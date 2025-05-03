/*
 * Humidity_Gauge.h
 *
 *  Created on: Apr 23, 2025
 *      Author: kunal
 */

#ifndef HUMIDITY_GAUGE_HUMIDITY_GAUGE_H_
#define HUMIDITY_GAUGE_HUMIDITY_GAUGE_H_

#include "main.h"
#include "BME280\BME280.h"

/* ---------- constants (SI) -------------------------------------- */
#define R_DA   287.05f    /* J·kg⁻¹·K⁻¹  gas constant, dry air   */
#define R_WV   461.5f     /* J·kg⁻¹·K⁻¹  gas constant, H₂O vapor  */
#define CP_DA  1.006f     /* kJ·kg⁻¹·K⁻¹ specific heat, dry air   */
#define CP_WV  1.86f      /* kJ·kg⁻¹·K⁻¹ specific heat, vapor     */
#define L_0    2501.0f    /* kJ·kg⁻¹     latent heat @ 0 °C       */
#define MW_MA  0.622f     /* M_w / M_d (18.02 / 28.97)           */


/* ---------- result container ------------------------------------ */
typedef struct {
    /* sensor inputs echoed back */
    float T;        /* °C   dry-bulb                                */
    float RH;       /* %    relative humidity                       */
    float P_kPa;    /* kPa  station pressure                        */

    /* derived psychrometrics */
    float p_sat;    /* kPa  saturation vapour pressure              */
    float p_v;      /* kPa  partial vapour pressure                 */
    float w;        /* kg/kg_dry  humidity (mixing) ratio           */
    float rho_v;    /* g/m³ absolute humidity                       */
    float T_dp;     /* °C   dew-point                               */
    float T_wb;     /* °C   wet-bulb  (Stull approximation)         */
    float h;        /* kJ/kg_dry  moist-air enthalpy                */
    float v;        /* m³/kg_dry specific volume                    */
    float rho;      /* kg/m³ moist-air density                      */
} psychro_t;

psychro_t psychro_from_bme280(float T_C,
                              float RH_pct,
                              float P_Pa);          /* BME280 gives Pa */




#endif /* HUMIDITY_GAUGE_HUMIDITY_GAUGE_H_ */
