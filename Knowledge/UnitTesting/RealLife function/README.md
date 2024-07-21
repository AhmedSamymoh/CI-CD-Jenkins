# Voltage Error Handling Documentation

## DC Voltage

### Over Voltage Error Handling

- **Condition:** `VMD_DcVoltage >= VMD_DCVM_CFG_MAX_VOLTAGE_THRESHOLD_SCALED_VOLTS`
- **Condition:** `VMD_DcVoltage < VMD_DCVM_CFG_MAX_VOLTAGE_THRESHOLD_SCALED_VOLTS && VMD_DcVoltage > VMD_DCVM_CFG_MAX_CLEAR_VOLTAGE_THRESHOLD_SCALED_VOLTS`
- **Condition:** `VMD_DcVoltage <= VMD_DCVM_CFG_MAX_CLEAR_VOLTAGE_THRESHOLD_SCALED_VOLTS`

### Under Voltage Error Handling

- **Condition:** `VMD_DcVoltage <= VMD_DCVM_CFG_MIN_VOLTAGE_THRESHOLD_SCALED_VOLTS`
- **Condition:** `VMD_DcVoltage > VMD_DCVM_CFG_MIN_VOLTAGE_THRESHOLD_SCALED_VOLTS && VMD_DcVoltage < VMD_DCVM_CFG_MIN_CLEAR_VOLTAGE_THRESHOLD_SCALED_VOLTS`
- **Condition:** `VMD_DcVoltage >= VMD_DCVM_CFG_MIN_CLEAR_VOLTAGE_THRESHOLD_SCALED_VOLTS`

## Battery Voltage

### Over Voltage

- **Condition:** `battery_voltage_mV >= VMD_BVMD_CFG_VOLTAGE_MAXIMUM_THRESHOLD_MV`
- **Condition:** `battery_voltage_mV <= VMD_BVMD_CFG_VOLTAGE_MAXIMUM_CLEAR_THRESHOLD_MV`

### Critical Over Voltage

- **Condition:** `battery_voltage_mV >= VMD_BVMD_CFG_VOLTAGE_MAXIMUM_CRITICAL_THRESHOLD_MV`
- **Condition:** `battery_voltage_mV <= VMD_BVMD_CFG_VOLTAGE_MAXIMUM_CRITICAL_CLEAR_THRESHOLD_MV`

### Under Voltage

- **Condition:** `battery_voltage_mV <= VMD_BVMD_CFG_VOLTAGE_MINIMUM_THRESHOLD_MV`
- **Condition:** `battery_voltage_mV >= VMD_BVMD_CFG_VOLTAGE_MINIMUM_CLEAR_THRESHOLD_MV`

### Critical Under Voltage

- **Condition:** `battery_voltage_mV <= VMD_BVMD_CFG_VOLTAGE_MINIMUM_CRITICAL_THRESHOLD_MV`
- **Condition:** `battery_voltage_mV >= VMD_BVMD_CFG_VOLTAGE_MINIMUM_CRITICAL_CLEAR_THRESHOLD_MV`

## Logic Supply Voltage (if `VMD_LV_MODE` is enabled)

### Over Voltage

- **Condition:** `BVMD_logic_supply_voltage_mV >= VMD_BVMD_CFG_RAW_LOGIC_SUPPLY_VOLTAGE_MAXIMUM_THRESHOLD`
- **Condition:** `BVMD_logic_supply_voltage_mV < VMD_BVMD_CFG_LOGIC_SUPPLY_VOLTAGE_MAXIMUM_CLEAR_THRESHOLD`

### Under Voltage

- **Condition:** `BVMD_logic_supply_voltage_mV <= VMD_BVMD_CFG_RAW_LOGIC_SUPPLY_VOLTAGE_MINIMUM_THRESHOLD`
- **Condition:** `BVMD_logic_supply_voltage_mV >= VMD_BVMD_CFG_LOGIC_SUPPLY_VOLTAGE_MINIMUM_CLEAR_THRESHOLD`
