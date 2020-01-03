uint8 MODE_AUTO = 0
uint8 MODE_LATERAL_CLOSED_LOOP = 1
uint8 MODE_SPEED_CLOSED_LOOP = 2
uint8 MODE_OPEN_LOOP = 3

uint8 LATERAL_KEEP_LANE = 0
uint8 LATERAL_CHANGE_LANE_P1 = 1
uint8 LATERAL_CHANGE_LANE_P2 = 2

uint8 SPEED_PARK                = 0
uint8 SPEED_ACC_CONST           = 1
uint8 SPEED_ACC_NORM            = 2
uint8 SPEED_ACC_FAST            = 3
uint8 SPEED_DCC_CONST_FOR_OBJS  = 4
uint8 SPEED_DCC_NORM_FOR_OBJS   = 5
uint8 SPEED_DCC_FAST_FOR_OBJS   = 6
uint8 SPEED_DCC_CONST_FOR_STOP  = 7
uint8 SPEED_DCC_NORM_FOR_STOP   = 8
uint8 SPEED_DCC_FAST_FOR_STOP   = 9
uint8 SPEED_DCC_CONST_FOR_CURV  = 10
uint8 SPEED_DCC_NORM_FOR_CURV   = 11
uint8 SPEED_DCC_FAST_FOR_CURV   = 12
uint8 SPEED_DCC_CONST_FOR_MAPL  = 13
uint8 SPEED_DCC_NORM_FOR_MAPL   = 14
uint8 SPEED_DCC_FAST_FOR_MAPL   = 15
uint8 SPEED_ESTOP_FOR_OBJS      = 16
uint8 SPEED_ESTOP_FOR_STOP      = 17

uint8 DIR_STRAIGHT = 0
uint8 DIR_TURN_LEFT = 1
uint8 DIR_TURN_RIGHT = 2

Header header

uint8 mode
WayPoint[] way_points
VehicleCmd open_loop_cmd
float64 speed
float64 final_speed
float64 distance
uint8 lateral_state
uint8 speed_state

########## STOP AT DEST ################################
bool stop_at_dest

uint8 direction
