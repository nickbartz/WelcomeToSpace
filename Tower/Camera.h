#ifndef CAMERA_H
#define CAMERA_H

class Camera {
public: 
	Camera();
	
	SDL_Rect camera_box;

	void updatecamera();
	void change_camera_velocity(bool is_x, int magnitude);

	int camera_vel_x = 0;
	int camera_vel_y = 0;

private:

};

Camera::Camera()
{
	camera_box.x = 0;
	camera_box.y = 0;
	camera_box.w = SCREEN_WIDTH;
	camera_box.h = SCREEN_HEIGHT;
}

void Camera::updatecamera()
{
	//Center the camera over the dot
	camera_box.x += camera_vel_x;
	camera_box.y += camera_vel_y;

	//Keep the camera in bounds
	if (camera_box.x < 0)
	{
		camera_box.x = 0;
	}
	if (camera_box.y < 0)
	{
		camera_box.y = 0;
	}
	if (camera_box.x > LEVEL_WIDTH - SCREEN_WIDTH)
	{
		camera_box.x = LEVEL_WIDTH - SCREEN_WIDTH;
	}
	if (camera_box.y > LEVEL_HEIGHT - SCREEN_HEIGHT)
	{
		camera_box.y = LEVEL_HEIGHT - SCREEN_HEIGHT;
	}
}

void Camera::change_camera_velocity(bool is_x, int magnitude)
{
	if (is_x) camera_vel_x = magnitude;
	else camera_vel_y = magnitude;
}

#endif