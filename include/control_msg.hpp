
/**
 * @brief msg to be published from mpc_controller
 *
 */
struct ControlMsg
{
    // time stamp
    double time_counter = 0.0;
    // uint64_t time_counter = 0;    // time counter for sync with simulator [msec]

    // control command
    double accel_cmd = 0.0; // [m/s^2]
    double steer_cmd = 0.0; // [rad]

    // // node status and flags
    // double mpc_status = 0.0;        // 0:INIT, 1: READY, 2: CTRL, 3: ERR
    // double mpc_execute_task = 0.0;  // 0:Normal-Track, 1: ACC-LK, 2: LC-Right, 3: LC-Left
    // double mpc_complete_flag = 0.0; // false: not done, true: done

    // frenet serret infomation
    double y_frenet = 0.0;   // Lateral deviation from reference path[m]
    double yaw_frenet = 0.0; // Lateral deviation angle from reference path[rad]
};