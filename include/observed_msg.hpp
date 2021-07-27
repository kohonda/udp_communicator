
/**
 * @brief msg to be published from VMC
 *
 */
struct ObservedMsg
{
    // time stamp
    // double time_stamp     = 0.0;  // Unix time
    double time_counter = 0;  // time counter for sync with simulator [msec]

    // ego vehicle status
    double ego_vehicle_speed       = 0.0;  // [m/s]
    double ego_vehicle_long_accel  = 0.0;  // [m/s^2]
    double ego_vehicle_lat_accel   = 0.0;  // [m/s^2]
    double ego_vehicle_yaw_rate    = 0.0;  // [rad/s] *Positive value for counter-clockwise rotation
    double ego_vehicle_steer_angle = 0.0;  // [rad] *Positive value for counter-clockwise rotation
    double ego_vehicle_pose_x_g    = 0.0;  // [m] * Vehicle center of G in global coordinate
    double ego_vehicle_pose_y_g    = 0.0;  // [m]
    double ego_vehicle_yaw_g       = 0.0;  // [rad] *Positive value for counter-clockwise rotation

    // VMC status
    double vmc_status       = 0;  // 0:INIT, 1: READY, 2: CTRL, 3: ERR
    double vmc_execute_task = 0;  // 0:Normal-Track, 1: ACC-LK, 2: LC-Right, 3: LC-Left
};
