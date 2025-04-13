#pragma once
#include <cstdint>

namespace offsets {

	inline constexpr uintptr_t
		uworld = 0x16F07B88,
		owning_game_instance = 0x200,
		levels = 0x1b8 ,
		actors = 0x208 ,
		local_players = 0x38 ,
		viewport_client = 0x78 ,
		player_controller = 0x30 ,
		player_state = 0x2b0 ,
		acknowledged_pawn = 0x350 ,
		player_camera_manager = 0x360 ,
		game_state = 0x188,
		player_array = 0x2c0 ,
		pawn_private = 0x320 ,
		current_weapon = 0xa80 ,
		current_vehicle = 0x2b50 ,
		fort_pyhsics_vehicle_configs = 0x1c80 ,
		weapon_data = 0x5e8,
		projectile_speed = 0x1e64 ,
		projectile_gravity = 0x1e68 ,
		character_movement = 0x330 ,
		b_is_dying = 0x720 ,
		b_is_dbno = 0x962 ,
		default_fly_time = 0x624 ,
		last_update_velocity = 0x378 ,
		primary_pickup_item_entry = 0x370 ,
		item_definition = primary_pickup_item_entry + 0x18 ,
		rarity = 0xa2 ,
		item_name = 0x40 ,
		team_id = 0x1259 ,
		mesh = 0x328 ,
		kill_score = 0x126c ,
		targeted_fort_pawn = 0x1980 ,
		component_space_transforms_array = 0x5C8 ,
		component_to_world = 0x1E0 ,
		root_component = 0x1b0 ,
		relative_location = 0x138 ,
		bounds_scale = 0x314 ,
		last_submit_time = bounds_scale + 0x4 ,
		last_render_time_on_screen = bounds_scale + 0x8 ,
		weapon_offset_correction = 0x2988;

} // namespace offsets