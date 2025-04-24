/*
 * Humidity_Gauge.c
 *
 *  Created on: Apr 23, 2025
 *      Author: kunal
 */


#include "Humidity_Gauge.h"


/* ---------- helper: Magnus saturation vapour pressure (0-60 °C) -- */
static inline float p_sat_kPa(float T_C)
{
    return 0.61078f * expf(17.269f * T_C / (T_C + 237.3f));   /* kPa */
}

/* ---------- helper: dew-point via inverse Magnus ----------------- */
static float dew_point(float p_v_kPa)
{
    float ln = logf(p_v_kPa / 0.61078f);
    return (237.3f * ln) / (17.269f - ln);                    /* °C  */
}

/* ---------- helper: Stull (2011) wet-bulb approximation ---------- */
static float wet_bulb_stull(float T_C, float RH_pct)
{
    float rh = RH_pct;
    float term1 = T_C * atanf(0.151977f * sqrtf(rh + 8.313659f));
    float term2 = atanf(T_C + rh);
    float term3 = atanf(rh - 1.676331f);
    float term4 = 0.00391838f * powf(rh, 1.5f) * atanf(0.023101f * rh);
    return term1 + term2 - term3 + term4 - 4.686035f;         /* °C */
}

/* ---------- public API ------------------------------------------ */
psychro_t psychro_from_bme280(float T_C,
                              float RH_pct,
                              float P_Pa)          /* BME280 gives Pa */
{
    psychro_t o;
    o.T      = T_C;
    o.RH     = RH_pct;
    o.P_kPa  = P_Pa * 0.001f;

    /* 1. saturation & partial pressures */
    o.p_sat  = p_sat_kPa(T_C);
    o.p_v    = (RH_pct * 0.01f) * o.p_sat;

    /* 2. humidity ratio & absolute humidity */
    o.w      = MW_MA * o.p_v / (o.P_kPa - o.p_v);
    o.rho_v  = (o.p_v * 1000.0f) / (R_WV * (T_C + 273.15f));  /* kg/m³ */
    o.rho_v *= 1000.0f;                                       /* → g/m³ */

    /* 3. dew-point & wet-bulb */
    o.T_dp   = dew_point(o.p_v);
    o.T_wb   = wet_bulb_stull(T_C, RH_pct);  /* good −20…50 °C, 5–99 % */

    /* 4. enthalpy */
    o.h      = CP_DA * T_C + o.w * (L_0 + CP_WV * T_C);

    /* 5. specific volume & density (moist air) */
    o.v      = (R_DA * (T_C + 273.15f) * (1.0f + 1.6078f * o.w)) / (o.P_kPa * 1000.0f);
    o.rho    = 1.0f / o.v;

    return o;
}
