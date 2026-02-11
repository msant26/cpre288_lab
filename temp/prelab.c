/**
 * This program contains 10 lines in the main function for the second prelab
 * @author Michael Santiago
 * @date 02/03/2026
 */

int main (void) {
    // initializes program to save memory
    oi_t *sensor_data = oi.allloc();
    oi_init(sensor_data);

    // rotates clockwise
    oi_setWheels(0, 500);

    // stops
    oi_setWheels(0,0);

    // rotates counterclockwise
    oi_setWheels(0, 500);

    // stops
    oi_setWheels(0,0);

    // moves forward full steam
    oi_setWheels(500, 500);

    // stops
    oi_setWheels(0,0);

    // frees memory
    oi_free(sensor_data);
    return 0;
}
