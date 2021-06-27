#ifndef _H_PM_
#define _H_PM_

#include "lse.h"

#define PM_CONFIG_NOP(pm)	(pm)->config_NOP
#define PM_CONFIG_TVM(pm)	(pm)->config_TVM
#define PM_CONFIG_IFB(pm)	(pm)->config_IFB
#define PM_CONFIG_DEBUG(pm)	(pm)->config_DEBUG

#define PM_TSMS(pm, ms)		(int) (pm->freq_hz * (ms) / 1000.f)

#define PM_HALL_SPAN		1.05f
#define PM_MAX_F		1000000000000.f
#define PM_SFI(s)		#s

enum {
	PM_NOP_THREE_PHASE			= 0,
	PM_NOP_TWO_PHASE
};

enum {
	PM_IFB_AB_INLINE			= 0,
	PM_IFB_AB_LOW,
};

enum {
	PM_SENSOR_DISABLED			= 0,
	PM_SENSOR_HALL,
	PM_SENSOR_ABI,
};

enum {
	PM_DISABLED				= 0,
	PM_ENABLED
};

enum {
	PM_DRIVE_CURRENT			= 0,
	PM_DRIVE_SPEED,
	PM_DRIVE_SERVO,
};

enum {
	PM_FLUX_UNCERTAIN			= 0,
	PM_FLUX_HIGH,
	PM_FLUX_LOCKED_IN_DETACH
};

enum {
	PM_LU_DISABLED				= 0,
	PM_LU_DETACHED,
	PM_LU_FORCED,
	PM_LU_ESTIMATE_FLUX,
	PM_LU_ESTIMATE_HFI,
	PM_LU_SENSOR_HALL,
	PM_LU_SENSOR_ABI,
};

enum {
	PM_STATE_IDLE				= 0,
	PM_STATE_ZERO_DRIFT,
	PM_STATE_SELF_TEST_BOOTSTRAP,
	PM_STATE_SELF_TEST_POWER_STAGE,
	PM_STATE_SELF_TEST_CLEARANCE,
	PM_STATE_ADJUST_VOLTAGE,
	PM_STATE_ADJUST_CURRENT,
	PM_STATE_PROBE_CONST_R,
	PM_STATE_PROBE_CONST_L,
	PM_STATE_LU_DETACHED,
	PM_STATE_LU_STARTUP,
	PM_STATE_LU_SHUTDOWN,
	PM_STATE_PROBE_CONST_E,
	PM_STATE_PROBE_CONST_J,
	PM_STATE_ADJUST_SENSOR_HALL,
	PM_STATE_LOOP_BOOST,
	PM_STATE_HALT,
};

enum {
	PM_OK					= 0,

	/* Internal.
	 * */
	PM_ERROR_ZERO_DRIFT_FAULT,
	PM_ERROR_NO_MOTOR_CONNECTED,
	PM_ERROR_BOOTSTRAP_TIME,
	PM_ERROR_POWER_STAGE_DAMAGED,
	PM_ERROR_LOW_ACCURACY,
	PM_ERROR_CURRENT_LOOP_IS_OPEN,
	PM_ERROR_INLINE_OVERCURRENT,
	PM_ERROR_DC_LINK_OVERVOLTAGE,
	PM_ERROR_INVALID_OPERATION,
	PM_ERROR_SENSOR_HALL_FAULT,
	PM_ERROR_SENSOR_ABI_FAULT,

	/* External.
	 * */
	PM_ERROR_TIMEOUT,
	PM_ERROR_NO_FLUX_CAUGHT,
	PM_ERROR_LOSS_OF_SYNC,		/* BLM model only */
};

typedef struct {

	float		current_A;
	float		current_B;
	float		voltage_U;

	float		voltage_A;
	float		voltage_B;
	float		voltage_C;

	int		pulse_HS;
	int		pulse_EP;
}
pmfb_t;

typedef struct {

	float		freq_hz;
	float		dT;

	int		dc_resolution;
	float		dc_minimal;
	float		dc_clearance;
	float		dc_skip;
	float		dc_bootstrap;
	float		dc_clamped;

	float		k_UMAX;
	float		k_EMAX;
	float		k_KWAT;
	int		k_ZNUL;

	int		ts_minimal;
	int		ts_clearance;
	int		ts_skip;
	int		ts_bootstrap;
	int		ts_clamped;
	float		ts_inverted;

	float		self_BST[3];
	int		self_BM[8];
	float		self_RMSi[3];
	float		self_RMSu[3];

	int		config_NOP;
	int		config_TVM;
	int		config_IFB;
	int		config_DEBUG;

	int		config_VSI_PRECISE;
	int		config_FORCED;
	int		config_FLUX;
	int		config_SKEW;
	int		config_HFI;
	int		config_MAJOR;
	int		config_SENSOR;
	int		config_ABI_REVERSED;
	int		config_ABI_DEBOUNCE;
	int		config_DRIVE;
	int		config_MTPA;
	int		config_WEAK;
	int		config_BRAKE;
	int		config_LIMIT;
	int		config_INFO;
	int		config_BOOST;

	int		debug_locked_HFI;
	int		debug_locked_SENSOR;

	int		fsm_req;
	int		fsm_state;
	int		fsm_phase;
	int		fsm_subi;
	int		fsm_errno;

	int		tm_value;
	int		tm_end;

	float		tm_transient_slow;
	float		tm_transient_fast;
	float		tm_voltage_hold;
	float		tm_current_hold;
	float		tm_instant_probe;
	float		tm_average_probe;
	float		tm_average_drift;
	float		tm_average_inertia;
	float		tm_startup;
	float		tm_halt_pause;

	float		ad_IA[2];
	float		ad_IB[2];
	float		ad_US[2];
	float		ad_UA[2];
	float		ad_UB[2];
	float		ad_UC[2];

	float		fb_iA;
	float		fb_iB;
	float		fb_uA;
	float		fb_uB;
	float		fb_uC;
	int		fb_HS;
	int		fb_EP;

	float		probe_current_hold;
	float		probe_hold_angle;
	float		probe_current_weak;
	float		probe_current_sine;
	float		probe_freq_sine_hz;
	float		probe_speed_maximal_pc;
	float		probe_speed_hold;
	float		probe_speed_detached;
	float		probe_gain_P;
	float		probe_gain_I;

	lse_t		probe_LS[3];

	float		fault_voltage_tol;
	float		fault_current_tol;
	float		fault_accuracy_tol;
	float		fault_current_halt;
	float		fault_voltage_halt;

	float		vsi_DC;
	float		vsi_X;
	float		vsi_Y;
	float		vsi_DX;
	float		vsi_DY;
	int		vsi_SA;
	int		vsi_SB;
	int		vsi_SC;
	int		vsi_TIM;
	int		vsi_AG;
	int		vsi_BG;
	int		vsi_CG;
	int		vsi_AF;
	int		vsi_BF;
	int		vsi_SF;
	int		vsi_UF;
	int		vsi_AZ;
	int		vsi_BZ;
	int		vsi_CZ;

	float		vsi_lpf_DC;
	float		vsi_gain_LP_F;

	int		tvm_ALLOWED;
	float		tvm_range_DC;
	float		tvm_A;
	float		tvm_B;
	float		tvm_C;
	float		tvm_FIR_A[3];
	float		tvm_FIR_B[3];
	float		tvm_FIR_C[3];
	float		tvm_DX;
	float		tvm_DY;

	float		lu_iX;
	float		lu_iY;
	float		lu_iD;
	float		lu_iQ;
	float		lu_F[2];
	float		lu_wS;
	int		lu_mode;

	float		lu_lpf_torque;
	float		lu_base_wS;
	float		lu_gain_TF;

	float		lu_F1;
	int		lu_revol;
	int		lu_revob;

	float		forced_F[2];
	float		forced_wS;
	float		forced_hold_D;
	float		forced_maximal;
	float		forced_reverse;
	float		forced_accel;
	int		forced_TIM;

	float		detach_X;
	float		detach_Y;
	float		detach_V[2];
	int		detach_TIM;
	int		detach_SKIP;
	float		detach_take_U;
	float		detach_gain_AD;
	float		detach_gain_SF;

	float		flux_X;
	float		flux_Y;
	float		flux_E;
	float		flux_F[2];
	float		flux_wS;
	float		flux_gain_IN;
	float		flux_gain_LO;
	float		flux_gain_HI;
	float		flux_gain_AD;
	float		flux_gain_SF;
	float		flux_gain_IF;

	int		flux_mode;
	int		flux_LOCKED;
	float		flux_lpf_wS;
	float		flux_MPPE;
	float		flux_gain_TAKE;
	float		flux_gain_GIVE;
	float		flux_gain_LEVE;
	float		flux_gain_LP_S;

	int		skew_ONFLAG;
	int		skew_TIM;
	int		skew_END;
	float		skew_ripple_STD;
	float		skew_KF[7];

	float		hfi_F[2];
	float		hfi_wS;
	float		hfi_inject_sine;
	float		hfi_maximal;
	float		hfi_wave[2];
	float		hfi_im_L1;
	float		hfi_im_L2;
	float		hfi_im_R;
	float		hfi_im_FP;
	int		hfi_DIV;
	int		hfi_SKIP;
	int		hfi_SUM;
	int		hfi_FLUX;
	float		hfi_DFT[9];
	float		hfi_REM[12];
	int		hfi_DFT_N;
	int		hfi_DFT_P;
	int		hfi_TIM;
	float		hfi_gain_SF;
	float		hfi_gain_IF;

	struct {

		float	X;
		float	Y;
	}
	hall_ST[8];

	int		hall_ALLOWED;
	int		hall_HS;
	int		hall_DIRF;
	float		hall_prolS;
	int		hall_prolTIM;
	float		hall_F[2];
	float		hall_wS;
	float		hall_prol_T;
	float		hall_gain_PF;
	float		hall_gain_SF;
	float		hall_gain_IF;

	int		abi_baseEP;
	float		abi_baseF[2];
	int		abi_lastEP;
	int		abi_rotEP;
	int		abi_prolTIM;
	float		abi_prolS;
	int		abi_PPR;
	float		abi_Zq;
	float		abi_F[2];
	float		abi_wS;
	float		abi_gain_PF;
	float		abi_gain_SF;
	float		abi_gain_IF;

	float		const_fb_U;
	float		const_E;
	float		const_R;
	int		const_Zp;
	float		const_Ja;
	float		const_im_L1;
	float		const_im_L2;
	float		const_im_B;
	float		const_im_R;
	float		const_ld_S;

	float		temp_const_ifbU;
	float		temp_const_iE;
	float		temp_HFI_wS;
	float		temp_HFI_HT[2];
	int		temp_prol_T;
	float		temp_ZiPPR;

	float		watt_wP_maximal;
	float		watt_iDC_maximal;
	float		watt_wP_reverse;
	float		watt_iDC_reverse;
	float		watt_dclink_HI;
	float		watt_dclink_LO;
	float		watt_lpf_D;
	float		watt_lpf_Q;
	float		watt_lpf_wP;
	float		watt_gain_LP_F;
	float		watt_gain_LP_P;

	float		i_setpoint_torque;
	float		i_maximal;
	float		i_reverse;
	float		i_derated_PCB;
	float		i_derated_HFI;
	float		i_derated_WEAK;
	float		i_track_D;
	float		i_track_Q;
	float		i_integral_D;
	float		i_integral_Q;
	float		i_slew_rate;
	float		i_slew_dT;
	float		i_tol_Z;
	float		i_gain_P;
	float		i_gain_I;

	float		weak_maximal;
	float		weak_D;
	float		weak_gain_EU;

	float		v_maximal;
	float		v_reverse;

	float		s_setpoint_speed;
	float		s_maximal;
	float		s_reverse;
	float		s_accel;
	float		s_linspan;
	float		s_track;
	float		s_tol_Z;
	float		s_gain_P;
	float		s_gain_S;
	float		s_iSP;

	float		x_setpoint_F[2];
	float		x_setpoint_speed;
	int		x_setpoint_revol;
	float		x_residual;
	float		x_tol_N;
	float		x_tol_Z;
	float		x_gain_P;
	float		x_gain_N;

	int		im_total_revol;
	int		im_base_revol;
	float		im_distance;
	float		im_consumed_Wh;
	float		im_consumed_Ah;
	float		im_reverted_Wh;
	float		im_reverted_Ah;
	float		im_capacity_Ah;
	float		im_fuel_pc;
	float		im_REM[4];

	float		boost_iIN_HI;
	float		boost_uIN_LO;
	float		boost_iDC_HI;
	float		boost_uDC_HI;
	float		boost_gain_P;
	float		boost_gain_I;

	void 		(* proc_set_DC) (int, int, int);
	void 		(* proc_set_Z) (int);
}
pmc_t;

void pm_default(pmc_t *pm);
void pm_build(pmc_t *pm);

void pm_tune_MPPE(pmc_t *pm);
void pm_tune_forced(pmc_t *pm);
void pm_tune_loop_current(pmc_t *pm);
void pm_tune_loop_speed(pmc_t *pm);

void pm_hfi_DFT(pmc_t *pm, float la[5]);

void pm_voltage(pmc_t *pm, float uX, float uY);
void pm_feedback(pmc_t *pm, pmfb_t *fb);

void pm_FSM(pmc_t *pm);

const char *pm_strerror(int n);

#endif /* _H_PM_ */

