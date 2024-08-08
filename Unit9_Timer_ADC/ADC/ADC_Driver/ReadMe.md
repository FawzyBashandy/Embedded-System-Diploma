# ATmega32 ADC Driver

This driver for the ATmega32 microcontroller provides a set of functions to control and utilize the ADC (Analog-to-Digital Converter). It supports both single and auto-triggered conversions and allows for flexible ADC configuration and result handling.

## Features

- **Initialization**: Configure ADC settings including clock prescaler, conversion mode, input channel, reference voltage, and trigger event.
- **Conversion**: Start both single and auto-triggered conversions. Retrieve conversion results and stop auto-triggered conversions.
- **Callback Handling**: Register a callback function to be invoked upon conversion completion.
- **Reset**: Restore ADC settings to default values.

## Functions

### `eStatus_t MCAL_ADC_Init(ADC_Config_t* ADCcfg)`

Initializes the ADC with provided settings.

**Parameters**:
- `ADCcfg`: Configuration settings.

**Returns**:
- `E_OK` on success, `E_NOK` on failure.

### `eStatus_t MCAL_ADC_Reset()`

Resets ADC to default settings.

**Returns**:
- `E_OK` on success.

### `eStatus_t MCAL_ADC_startConversion()`

Starts an ADC conversion. Supports both:
- **Single Conversion**: Initiates a one-time conversion.
- **Auto-Triggered Conversion**: Starts conversion with automatic triggering based on configured events.

**Returns**:
- `E_OK` on success.

### `eStatus_t MCAL_ADC_autoConversionStop()`

Stops auto-triggered conversions and waits for the current conversion to finish.

**Returns**:
- `E_OK` on success.

### `eStatus_t MCAL_ADC_changeInputChannel(eADC_InputChannel channel)`

Changes the ADC input channel and resumes conversion.

**Parameters**:
- `channel`: New input channel.

**Returns**:
- `E_OK` on success, `E_NOK` on failure.

### `eStatus_t MCAL_ADC_getConversionResult(uint16_t *pBuffer)`

Gets the result of the ADC conversion.

**Parameters**:
- `pBuffer`: Storage for the result.

**Returns**:
- `E_OK` on success, `E_NOK` on failure.

### `eStatus_t MCAL_ADC_setEndOfConversion_CALLBACK(void (*callback)(void))`

Sets a callback function for when conversion completes.

**Parameters**:
- `callback`: Function to be called upon completion.

**Returns**:
- `E_OK` on success, `E_NOK` on failure.

