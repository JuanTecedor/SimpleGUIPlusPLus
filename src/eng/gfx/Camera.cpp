#include "Camera.hpp"

#include <cassert>

bool Camera::inside_view_port(const PositionF & other_pos) const
{
	return (
		position.x - view_port.x / 2 <= other_pos.x
		&& other_pos.x <= position.x + view_port.x / 2
		&& position.y - view_port.y / 2 <= other_pos.y
		&& other_pos.y <= position.y + view_port.y / 2
	);
}

void Camera::change_zoom(const Camera::Zoom & new_zoom)
{
	if(new_zoom == Zoom::ZOOM_IN)
	{
		zoom += ZOOM_DELTA;
	}
	else if(new_zoom == Zoom::ZOOM_OUT)
	{
		zoom -= ZOOM_DELTA;
	}
	else
	{
		assert(false);
	}
	view_port = starting_view_port * zoom;
}
