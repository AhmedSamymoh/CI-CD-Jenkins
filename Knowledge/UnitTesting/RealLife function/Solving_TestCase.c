#include <assert.h>
#include <stdio.h>
#include <stdint.h>

typedef struct {
    int event;
    int status;
} AEVM_EventReport_Call;

#define MAX_AEVM_CALLS 100
static AEVM_EventReport_Call AEVM_EventReport_calls[MAX_AEVM_CALLS];
static int AEVM_EventReport_call_count = 0;

void AEVM_EventReport(int event, int status) {
    if (AEVM_EventReport_call_count < MAX_AEVM_CALLS) {
        AEVM_EventReport_calls[AEVM_EventReport_call_count].event = event;
        AEVM_EventReport_calls[AEVM_EventReport_call_count].status = status;
        AEVM_EventReport_call_count++;
    }
}

void reset_AEVM_EventReport_calls() {
    AEVM_EventReport_call_count = 0;
}

#define VMD_DCVM_CFG_MAX_VOLTAGE_THRESHOLD_SCALED_VOLTS 100
#define VMD_DCVM_CFG_MAX_CLEAR_VOLTAGE_THRESHOLD_SCALED_VOLTS 95
#define VMD_DCVM_CFG_MIN_VOLTAGE_THRESHOLD_SCALED_VOLTS 10
#define VMD_DCVM_CFG_MIN_CLEAR_VOLTAGE_THRESHOLD_SCALED_VOLTS 15

#define VMD_BVMD_CFG_VOLTAGE_MAXIMUM_THRESHOLD_MV 1200
#define VMD_BVMD_CFG_VOLTAGE_MAXIMUM_CLEAR_THRESHOLD_MV 1100
#define VMD_BVMD_CFG_VOLTAGE_MAXIMUM_CRITICAL_THRESHOLD_MV 1500
#define VMD_BVMD_CFG_VOLTAGE_MAXIMUM_CRITICAL_CLEAR_THRESHOLD_MV 1400
#define VMD_BVMD_CFG_VOLTAGE_MINIMUM_THRESHOLD_MV 900
#define VMD_BVMD_CFG_VOLTAGE_MINIMUM_CLEAR_THRESHOLD_MV 950
#define VMD_BVMD_CFG_VOLTAGE_MINIMUM_CRITICAL_THRESHOLD_MV 600
#define VMD_BVMD_CFG_VOLTAGE_MINIMUM_CRITICAL_CLEAR_THRESHOLD_MV 700

uint16_t VMD_DcVoltage         = 0;
uint16_t battery_voltage_mV	   = 0;

void VMD_SlowCycle(void) {
    static uint8_t last_status_reported_ov = 0;
    static uint8_t last_status_reported_uv = 0;
    static uint8_t ov_status  = 0;
    static uint8_t uv_status  = 0;
    static uint8_t cov_status = 0;
    static uint8_t cuv_status = 0;
	
	
	
	
	/* Event Type 1: DC over-voltage condition.
	Event Type 2: DC under-voltage condition.
	Event Type 3: Battery over-voltage condition.	
	Event Type 4: Battery critical over-voltage condition.
	Event Type 5: Battery under-voltage condition.
	Event Type 6: Battery critical under-voltage condition.
	The status (1 or 0) indicates whether the condition is active (1) or cleared (0).
	
	
	*/
	
	#define DC_over_voltage 					1
	#define DC_under_voltage 					2
	#define Battery_over_voltage 				3
	#define Battery__critical_over_voltage 		4
	#define Battery_under_voltage  				5
	#define Battery__critical_under_voltage		6
	
/*using the fun uint16_t VMD_DcVoltage; to store the values of the error handling into thhe struct*/
    if (VMD_DcVoltage >= VMD_DCVM_CFG_MAX_VOLTAGE_THRESHOLD_SCALED_VOLTS) {
		/*raising the error flag*/
        last_status_reported_ov = 1;
        AEVM_EventReport(DC_over_voltage, 1);
    } else if (VMD_DcVoltage < VMD_DCVM_CFG_MAX_VOLTAGE_THRESHOLD_SCALED_VOLTS && VMD_DcVoltage > VMD_DCVM_CFG_MAX_CLEAR_VOLTAGE_THRESHOLD_SCALED_VOLTS) {
        if (last_status_reported_ov == 1) {
            AEVM_EventReport(DC_over_voltage, 1);
        } else {
            AEVM_EventReport(DC_over_voltage, 0);
        }
    } else {
		/*lowering the error flag if there's no problem with the DCValue*/
        AEVM_EventReport(DC_over_voltage, 0);
        last_status_reported_ov = 0;
    }


/*                                   UNDER VOLTAGE                                     */
    if (VMD_DcVoltage <= VMD_DCVM_CFG_MIN_VOLTAGE_THRESHOLD_SCALED_VOLTS) {
        last_status_reported_uv = 1;
        AEVM_EventReport(DC_under_voltage , 1);
    } else if (VMD_DcVoltage > VMD_DCVM_CFG_MIN_VOLTAGE_THRESHOLD_SCALED_VOLTS && VMD_DcVoltage < VMD_DCVM_CFG_MIN_CLEAR_VOLTAGE_THRESHOLD_SCALED_VOLTS) {
        if (last_status_reported_uv == 1) {
            AEVM_EventReport(DC_under_voltage , 1);
        } else {
            AEVM_EventReport(DC_under_voltage , 0);
        }
    } else {
        AEVM_EventReport(DC_under_voltage , 0);
        last_status_reported_uv = 0;
    }
	
	
	
	
	//the battery analysis
    if (battery_voltage_mV >= VMD_BVMD_CFG_VOLTAGE_MAXIMUM_THRESHOLD_MV) {
        ov_status = 1;
    } else if (battery_voltage_mV <= VMD_BVMD_CFG_VOLTAGE_MAXIMUM_CLEAR_THRESHOLD_MV) {
        ov_status = 0;
    }

    if (battery_voltage_mV >= VMD_BVMD_CFG_VOLTAGE_MAXIMUM_CRITICAL_THRESHOLD_MV) {
        cov_status = 1;
    } else if (battery_voltage_mV <= VMD_BVMD_CFG_VOLTAGE_MAXIMUM_CRITICAL_CLEAR_THRESHOLD_MV) {
        cov_status = 0;
    }

    if (battery_voltage_mV <= VMD_BVMD_CFG_VOLTAGE_MINIMUM_THRESHOLD_MV) {
        uv_status = 1;
    } else if (battery_voltage_mV >= VMD_BVMD_CFG_VOLTAGE_MINIMUM_CLEAR_THRESHOLD_MV) {
        uv_status = 0;
    }

    if (battery_voltage_mV <= VMD_BVMD_CFG_VOLTAGE_MINIMUM_CRITICAL_THRESHOLD_MV) {
        cuv_status = 1;
    } else if (battery_voltage_mV >= VMD_BVMD_CFG_VOLTAGE_MINIMUM_CRITICAL_CLEAR_THRESHOLD_MV) {
        cuv_status = 0;
    }
	/*Storing the status of the Battery*/
    AEVM_EventReport(Battery_over_voltage, ov_status);
    AEVM_EventReport(Battery__critical_over_voltage , cov_status);
    AEVM_EventReport(Battery_under_voltage, uv_status);
    AEVM_EventReport(Battery__critical_under_voltage	, cuv_status);
}




void test_dc_over_voltage() {
	/*This line should generate an over thershold error*/
    VMD_DcVoltage = VMD_DCVM_CFG_MAX_VOLTAGE_THRESHOLD_SCALED_VOLTS + 15;
    reset_AEVM_EventReport_calls();
    VMD_SlowCycle();
    assert(AEVM_EventReport_call_count == 1);
    assert(AEVM_EventReport_calls[0].event == DC_over_voltage );
    assert(AEVM_EventReport_calls[0].status == 1);
    printf("test_dc_over_voltage passed\n");
}


void test_dc_under_voltage() {
    VMD_DcVoltage = VMD_DCVM_CFG_MIN_VOLTAGE_THRESHOLD_SCALED_VOLTS - 1;
    reset_AEVM_EventReport_calls();
    VMD_SlowCycle();
    assert(AEVM_EventReport_call_count == 1);
    assert(AEVM_EventReport_calls[0].event == DC_under_voltage 	);
    assert(AEVM_EventReport_calls[0].status == 1);
    printf("test_dc_under_voltage passed\n");
}


void test_battery_over_voltage() {
    battery_voltage_mV = VMD_BVMD_CFG_VOLTAGE_MAXIMUM_THRESHOLD_MV + 1;
    reset_AEVM_EventReport_calls();
    VMD_SlowCycle();
    assert(AEVM_EventReport_call_count == 1);
    assert(AEVM_EventReport_calls[0].event == Battery_over-voltage );
    assert(AEVM_EventReport_calls[0].status == 1);
    printf("test_battery_over_voltage passed\n");
}

void test_battery_under_voltage() {
    battery_voltage_mV = VMD_BVMD_CFG_VOLTAGE_MINIMUM_THRESHOLD_MV - 1;
    reset_AEVM_EventReport_calls();
    VMD_SlowCycle();
    assert(AEVM_EventReport_call_count == 1);
    assert(AEVM_EventReport_calls[0].event == Battery_under_voltage);
    assert(AEVM_EventReport_calls[0].status == 1);
    printf("test_battery_under_voltage passed\n");
}

void test_battery_critical_over_voltage() {
    battery_voltage_mV = VMD_BVMD_CFG_VOLTAGE_MAXIMUM_CRITICAL_THRESHOLD_MV + 1;
    reset_AEVM_EventReport_calls();
    VMD_SlowCycle();
    assert(AEVM_EventReport_call_count == 1);
    assert(AEVM_EventReport_calls[0].event == Battery__critical_over_voltage );
    assert(AEVM_EventReport_calls[0].status == 1);
    printf("test_battery_critical_over_voltage passed\n");
}

void test_battery_critical_under_voltage() {
    battery_voltage_mV = VMD_BVMD_CFG_VOLTAGE_MINIMUM_CRITICAL_THRESHOLD_MV - 1;
    reset_AEVM_EventReport_calls();
    VMD_SlowCycle();
    assert(AEVM_EventReport_call_count == 1);
    assert(AEVM_EventReport_calls[0].event == Battery__critical_under_voltage);
    assert(AEVM_EventReport_calls[0].status == 1);
    printf("test_battery_critical_under_voltage passed\n");
}



int main() {
    test_dc_over_voltage();
    test_dc_under_voltage();
    test_battery_over_voltage();
    test_battery_under_voltage();
    test_battery_critical_over_voltage();
    test_battery_critical_under_voltage();
    return 0;
}
