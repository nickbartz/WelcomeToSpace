#ifndef CAMERA_H
#define CAMERA_H

class Camera {
public: 
	Camera();
	
	SDL_Rect camera_box;

	void updatecamera(int dot_x, int dot_y);

private:

};

Camera::Camera()
{
	camera_box.x = 0;
	camera_box.y = 0;
	camera_box.w = SCREEN_WIDTH;
	camera_box.h = SCREEN_HEIGHT;
}

void Camera::updatecamera(int dot_x, int dot_y)
{
	//Center the camera over the dot
	camera_box.x = dot_x;
	camera_box.y = dot_y;

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

#endif