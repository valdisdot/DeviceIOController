This repository contains the source code for *the embedded side* of the **DeviceIO** project.

**DeviceIO Controller: version 1.1**

## Main concept

The main concept of the logic branch `device-server` revolves around a simple *state exchange* and *request-response* model.

Devices interact by sending or receiving raw port values and specific commands either to/from the server (via MQTT) or the local client (via a serial connection).

The responsibility for *data interpretation* lies outside the scope of the device's logic. For example, if a device's port sends a value like `2000`, the *server or client* assigns a real physical meaning to this value.

All data exchanges (messages) follow a structured *JSON* format. This applies to state exchange, request/response operations, and even logging, ensuring a unified and consistent communication model.

## Device messages

### State message

Represents a state message. The message hold port `modes` and `data` in arrays, with equal size. Device sends this type of message to the server on demand (by sending `send_state` request) or with specified `transmission_interval`.

```json
{
  "timestamp": 30064,
  "modes": [
    1,
    0,
    1,
    1,
    3,
    3
  ],
  "data": [
    0,
    -1,
    0,
    1,
    2784,
    148
  ]
}
```

- `timestamp` contains the amount of milliseconds since the device start.
- `modes` contains an array of port modes, where each `array index matches port number`.
  - `0` mode is `not initialized`, `data` value always will be `-1`.
  - `1` mode for `logical input`, meaning if the signal is present or not on the port, the `data` value is going to be `1` or `0` respectively.
  - `2` mode is `logical output`, otherwise the port state can be changed to the `low` or `high` value by a user with logical state of `0` or `1`, `data` value will hold the `last value`.
  - `3` mode is `values input`, meaning the voltage level of the port will be interpreted as an integer, the `data` value is going to be in range `from 0 to 4096`.
  - `4` mode is `value output`, otherwise the port state can be changed by a user in a range `from 0 to 4096` with respectful voltage level, `data` value will hold the `last value`.
  - `5` mode is `inversed logical input`, meaning if the signal is present (0) or not (1) on the port, the `data` value is going to be `1` or `0` respectively as for the `logical input` (useful for mechanical buttons).
  - `6` mode is `stateful logical input`, meaning the device will hold the last state of the port and inverse the saved value if the port's state changes, otherwise `data` value will be `n%2`, where `n is port state changes count` (useful for stateful buttons, clicker). User can also change the value in this mode as the `logical output`.
  - `10` mode is `forbidden to use`, act as the same as the `not initialized`, but shows the `intention` of not to use the port, `data` value always will be `-1`.
- `data` containts an array of actual port values. As for `modes`, each `array index matches port number`.

### Controller's state message

Represents a controller state message. The message contains information about `network mode`, `level of the metwork signal`, `free RAM memory` and `last reboot reason`. Device sends this type of message to the server on demand (by sending `send_controller_state` request) and at the device start.

```json
{
  "timestamp": 1356,
  "mode": 2,
  "signal_strength": -52,
  "memory": 166428,
  "reboot_reason": 1,
}
```

- `timestamp` contains the amount of milliseconds since the device start.
- `mode` containt the digital value for `network connection mode`. IP-based modes transfer the data over MQTT.
  - `1` represents the digital value for the `serial` connection.
  - `2` represents the digital value for the `wifi` connection.
  - `3` represents the digital value for the `cellular` connection.
- `signal_strength` represents the `signal level` in millidecibels (mdB). Value `-1` means that the level has not been measured yet or the controller mode is `serial`.
- `memory` represents the `free RAM memory` in bytes.
- `reboot_reason` represents the digital value of the reboot reason (currently matches the `ESP reboot reasons`), see at [ESP Reset reasons (line 22)](https://github.com/espressif/esp-idf/blob/master/components/esp_system/include/esp_system.h).

### Log message

Represents a log message. The message contains `log level` and three level of detailization: `module` as a log message source, `message` as a description and `cause` which may containt `any type` of information or can be even `absent`.

```json
{
  "timestamp": 178356,
  "level": "ERROR",
  "module": "CLIENT.MESSAGE.REQUEST",
  "message": "Request isn't known",
  "cause": "{\"name\":\"some_unknown_stuff\"}"
}
```

- `timestamp` contains the amount of milliseconds since the device start.
- `level` represents the typical `log level`. Present levels are `DEBUG`, `INFO`, `WARNING` and `ERROR`.
- `module` represens a source of the message.
- `message` represents a details or description.
- `cause` hold additional information (buffers, json etc), can be `absent`.

### Request and response messages

The main concept of execution the device commands being sent from a user is a *request-response* model. In common, user sends a message with a `user-defined message identifier` (or `message_id`) and an `array of requests`.

`message_id` serves as a common reference to link the request message with its corresponding response and is sent back to the user.

`request` array holds the `objects` of actual request, with request name if the `name` field and its specified parameters in the `value` field.

```json
{
  "message_id": 12345,
  "request": [
    {
      "name": "request A name",
      "value": "request A value, array or object"
    },
    {
      "name": "request B name",
      "value": "request B value, array or object"
    }
  ]
}
```

- `message_id` represents a `user-defined message identifier` that will be sent back to the user.
- `request` - an array of `objects` of actual requests.
  - `name` - the request name.
  - `value`- parameter for the specified request. Depending on the request name, this field can be any type (`object`, `array`, `integer` etc.) or `absent`.

After the `request` is processed, the device sends a `response` back to the user, including the `message_id` field.

The response contains a `response` array of objects. Each object includes the request `name` and a digital representation of the execution `result`.  

```json
{
  "timestamp": 567890,
  "message_id": 12345,
  "response": [
    {
      "name": "request A name",
      "result": 1
    },
    {
      "name": "request B name",
      "result": 0
    }
  ]
}
```

- `timestamp` contains the amount of milliseconds since the device start.
- `message_id` represents a `user-defined message identifier` that is sent back to the user from the request message.
- `response` - an array of `objects` of responses to each request.
  - `name` - the request name.
  - `result` - request execution result.
    - `1` - request was `succesfully executed`.
    - `0` - request was `not executed` and was forvard as a log-message with `WARNING` level.
    - `-1` - request was `not known` and was forvard as a log-message with `ERROR` level.

## List of available device request

### `set_modes`

Sets the port modes in the device. The request supports `value` as an `array` and as an `object`.  

```json
{
  "message_id": 12345,
  "request": [
    {
      "name": "set_modes",
      "value": [0, 0, 0, 1, 0, 2, 2, 3, 3, 10]
    }
  ]
}
```

The `value` must be provided as an `array`, where each index corresponds to a `port number`, and each value is mapped to the respective `port mode`. If the user has 34 ports, the array must include values for all of them, covering each element from index 0 to 33.

```json
{
  "message_id": 545454,
  "request": [
    {
      "name": "set_modes",
      "value": {
        "4": 1,
        "19": 2,
        "26": 4
      }
    }
  ]
}
```

The `value` must be provided as an `object`, where each field name is treated as a `number` and mapped to a `port number`, while the corresponding field value is mapped to the `port mode`.

### `set_data`

Sets the port data in the device. The request supports `value` as an `array` and as an `object`.  

```json
{
  "message_id": 12345,
  "request": [
    {
      "name": "set_data",
      "value": [0, 0, 0, 1, 0, 100, 1, 0, 0, 0]
    }
  ]
}
```

The `value` must be provided as an `array`, where each index corresponds to a `port number`, and each value is mapped to the respective `port data`. If the user has 34 ports, the array must include values for all of them, covering each element from index 0 to 33.

```json
{
  "message_id": 12345,
  "request": [
    {
      "name": "set_data",
      "value": {
        "3": 1,
        "5": 100,
        "6": 1,
        "8": 0
      }
    }
  ]
}
```

The `value` must be provided as an `object`, where each field name is treated as a `number` and mapped to a `port number`, while the corresponding field value is mapped to the `port data`.

### `configure_network`

Configures the network connection mode and its related settings for the device.  

```json
{
  "message_id": 12345,
  "request": [
    {
      "name": "configure_network",
      "value": {
        "mode": 2,
        "ssid": "my_wifi",
        "password": "pwd12345",
        "apn_name": "internet",
        "apn_user": "internet",
        "apn_password": "12345"
      }
    }
  ]
}
```

The `value` for this request must be present as a `json-object`.

- `mode` containt the digital value for `network connection mode`.
  - `1` represents the digital value for the `serial` connection.
  - `2` represents the digital value for the `wifi` connection.
  - `3` represents the digital value for the `cellular` connection.
- `ssid` field represents the Wi-Fi SSID. Mandatory only for mode `2` (wifi).
- `password` field represents the Wi-Fi password. Mandatory only for mode `2` (wifi).
- `apn_name` field represents the Access Point Name (APN) for the cellular connection.
- `apn_user` and `apn_password` fields represent the username and password for authenticating the cellular connection to the Access Point Name (APN). These fields are optional for most modern operators but remain available for configurations requiring them.

### `configure_server`

Configures the server connection settings for the device.  

```json
{
  "message_id": 12345,
  "request": [
    {
      "name": "configure_server",
      "value": {
        "address": "16.167.29.201",
        "port": 8883,
        "user": "device",
        "password": "pwd12345",
        "certificate": "-----BEGIN CERTIFICATE-----
            MIIEczCCA1ugAwIBAgIBADANBgkqhkiG9w0BAQQFAD..AkGA1UEBhMCR0Ix
            ...
            7vQMfXdGsRrXNGRGnX+vWDZ3/zWI0joDtCkNnqEpVn..HoX
            -----END CERTIFICATE-----"
      }
    }
  ]
}
```

The `value` for this request must be present as a `json-object`.

`address` - specifies the server's IP address or domain name to which the device connects.
`port` - indicates the server's communication port.
`user` - represents the username used for authentication.
`password` - represents the password used for authentication.
`certificate` - contains the SSL/TLS certificate for establishing a secure connection to the server.

### `configure_controller`

Configures device settings as `log level` and `transmission interval`, determining `how frequently` the device will send `state data` to the server.

```json
{
  "message_id": 12345,
  "request": [
    {
      "name": "configure_server",
      "value": {
        "log_level": 10,
        "transmission_interval": 2000
      }
    }
  ]
}
```

The `value` for this request must be present as a `json-object`.

- `log_level` in digital value, sets the system logging level.
  - `0` for `DEBUG`.
  - `1` for `INFO`.
  - `2` for `WARNING`.
  - `10` for `ERROR`.
- `transmission_interval` configures the interval, in milliseconds, at which the device will send the port state.

### `send_state`

Request to send the state of the ports (`state message`).

```json
{
  "message_id": 12345,
  "request": [
    {
      "name": "send_state"
    }
  ]
}
```

No `value` required for this type of `request`

### `send_controller_state`

Request to send the state of the controller (`controller state message`).

```json
{
  "message_id": 12345,
  "request": [
    {
      "name": "send_controller_state"
    }
  ]
}
```

No `value` required for this type of `request`

### `make_backup`

Request trigger the device to `make a backup`, including configurations, port modes and data.

```json
{
  "message_id": 12345,
  "request": [
    {
      "name": "make_backup"
    }
  ]
}
```

No `value` required for this type of `request`

### `reboot`

Request trigger the controller to make a `soft reboot`. The device will go thoght the initialization phase again, read all data from the internal memory, timestamp will be reset.

```json
{
  "message_id": 12345,
  "request": [
    {
      "name": "reboot"
    }
  ]
}
```

No `value` required for this type of `request`


## Connectors and Device Identifier

The device operates with messages and data exchange via `Connectors`. All data formats are consistent across all connector types. The user implements the data exchange logic and processes the data on their own side.

Each device has an `id`, which is calculated from the device's WiFi `MAC address` (currently, by performing an XOR operation on each MAC byte). In order to communicate with a device, the user must know its id.

ID computation pseudo-code:

```pseudo
int mac_base[6];
put_mac_address(mac_base);
for(int i = 0; i < 6; ++i) 
    mac_base[i] = mac_base[i] ^ 127;
buffer = new char[32];
snprintf(buffer, "%d%d%d%d%d%d", mac_base);
```

### Supported connector types

1. **SerialConnector**
    - Transmits data via a serial connection on `HardwareSerial1` at a baud rate of `38400`.
    - Messages are flushed into the serial connection with a delimiter `
#END#
` to help the user distinguish between messages.
    - This is the `default connector`. The device switches to this mode if any initialization error occurs.

    On the first run, the serial connection is *soft-locked*. You must send the `device id` to unlock it.

    The user is responsible for implementing the logic for sending and receiving requests/data to the device via the serial connection. The device will periodically check for incoming data and respond to requests.

2. **MqttConnector**
    - Transmits data via an `MQTT broker` (using the `Client` class). Currently, `WiFiClient` and `WiFiClientSecure` are supported.
    - The user configures this type of connector through `configure_network` and `configure_server` requests.

    The user must implement the data processing logic. The device simply exchanges data with the `MQTT broker` using specific `topics`.

Topic List:

- `from/{$id}/state` - device publishes its `port state`.
- `from/{$id}/controller` - device publishes its `controller state`.
- `from/{$id}/log` - device publishes `logs`.
- `to/{$id}/request` - device subscribes to this topic to process `requests`.
- `from/{$id}/response` - device publishes `responses` to request processing.
