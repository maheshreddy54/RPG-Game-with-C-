import pixy2
import time
import pigpio



# Initialize Pixy2
pixy = pixy2.Pixy2()

# Initialize the Pixy2 camera
pixy.init()

# Setup pigpio
pi = pigpio.pi()
if not pi.connected:
    exit()


# Define the GPIO pin for the servo aim
AIM_PIN = 18

# Define the GPIO pin for the shooter
SHOOTER_PIN = 21

# Attach servo to pin
pi.set_mode(AIM_PIN, pigpio.OUTPUT)
pi.set_mode(SHOOTER_PIN, pigpio.OUTPUT)

# Define Servo postion variables
position = 90

# Convert angle to PWM
def set_servo_angle(servo_pin, angle):
    if 0 <= angle <= 180:
        # Convert angle to pulse width (microseconds)
        pulse_width = int(500 + (angle / 180) * 2000)
        pi.set_servo_pulsewidth(servo_pin, pulse_width)


# Set Shooter
def set_shooter():
    set_servo_angle(SHOOTER_PIN, 180)  # Move servo to 180 degrees
    time.sleep(3)  # Wait for 3 seconds
    set_servo_angle(SHOOTER_PIN, 0)  # Return to 0 degrees

# Define the servo control function
def set_aim_position(position):
    set_servo_angle(AIM_PIN, position)

# You should set the Pixy2 camera to detect color signatures and position.

def get_blue_object_position():
    global position
    # Get the blocks detected by Pixy2
    blocks = pixy.get_blocks()

    if len(blocks) > 0:

        for block in blocks:
    
            # Check if the block has the correct signature (e.g., Signature 1 for blue)

            if block.signature == 1:
                # Calculate the center of the block
                block_center_x = block.x + block.width / 2
                
                obj_max = 320 - block.width / 2
                obj_min = block.width / 2

                # Mapping obj position on pixy to angles 45 to 135 degrees
                position = (block_center_x - obj_min)/(obj_max - obj_min) * (135 - 45) + 45

                print(f"Blue object detected at: {position}")
                return position

    else:
        print("No objects detected")
        return None
       
    
def main():
    try:
        while True:
            position = get_blue_object_position()
            if (position!=None):
                set_aim_position(position)
                time.sleep(1)
                set_shooter()
            
    except KeyboardInterrupt:
        print("Program interrupted")
        pixy.close()

if __name__ == "__main__":
    main()