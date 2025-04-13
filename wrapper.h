#pragma once
#include <thirdparty/imgui/imgui.h>
#include <thirdparty/imgui/imgui_impl_win32.h>
#include <thirdparty/imgui/imgui_impl_dx11.h>
#include <thirdparty/imgui/imgui_internal.h>
#include <src/engine/sdk.h>


void box( ImDrawList* drawlist , const bounds& player_bounds , const ImColor& col , float thickness )
{
	const float box_width = player_bounds.max_x - player_bounds.min_x;
	const float box_height = player_bounds.max_y - player_bounds.min_y;

	drawlist->AddRect( ImVec2( player_bounds.min_x , player_bounds.min_y ) , ImVec2( player_bounds.min_x + box_width , player_bounds.min_y + box_height ) , col , 0 , 0 , thickness );

}

void cornered_box( ImDrawList* drawlist , const bounds& player_bounds , const ImColor& col , bool outlined , float thickness )
{
	const float box_width = player_bounds.max_x - player_bounds.min_x;
	const float box_height = player_bounds.max_y - player_bounds.min_y;
	const float corner_size = box_width * 0.2f;

	ImColor outline_color = ImColor( 0 , 0 , 0 , 255 );

	if ( outlined ) {
		drawlist->AddLine( ImVec2( player_bounds.min_x - 1 , player_bounds.min_y - 1 ) , ImVec2( player_bounds.min_x + corner_size + 1 , player_bounds.min_y - 1 ) , outline_color , thickness * 2 );
		drawlist->AddLine( ImVec2( player_bounds.min_x - 1 , player_bounds.min_y - 1 ) , ImVec2( player_bounds.min_x - 1 , player_bounds.min_y + corner_size + 1 ) , outline_color , thickness * 2 );

		drawlist->AddLine( ImVec2( player_bounds.max_x + 1 , player_bounds.min_y - 1 ) , ImVec2( player_bounds.max_x - corner_size - 1 , player_bounds.min_y - 1 ) , outline_color , thickness * 2 );
		drawlist->AddLine( ImVec2( player_bounds.max_x + 1 , player_bounds.min_y - 1 ) , ImVec2( player_bounds.max_x + 1 , player_bounds.min_y + corner_size + 1 ) , outline_color , thickness * 2 );

		drawlist->AddLine( ImVec2( player_bounds.min_x - 1 , player_bounds.max_y + 1 ) , ImVec2( player_bounds.min_x + corner_size + 1 , player_bounds.max_y + 1 ) , outline_color , thickness * 2 );
		drawlist->AddLine( ImVec2( player_bounds.min_x - 1 , player_bounds.max_y + 1 ) , ImVec2( player_bounds.min_x - 1 , player_bounds.max_y - corner_size - 1 ) , outline_color , thickness * 2 );

		drawlist->AddLine( ImVec2( player_bounds.max_x + 1 , player_bounds.max_y + 1 ) , ImVec2( player_bounds.max_x - corner_size - 1 , player_bounds.max_y + 1 ) , outline_color , thickness * 2 );
		drawlist->AddLine( ImVec2( player_bounds.max_x + 1 , player_bounds.max_y + 1 ) , ImVec2( player_bounds.max_x + 1 , player_bounds.max_y - corner_size - 1 ) , outline_color , thickness * 2 );
	}

	drawlist->AddLine( ImVec2( player_bounds.min_x , player_bounds.min_y ) , ImVec2( player_bounds.min_x + corner_size , player_bounds.min_y ) , col , thickness );
	drawlist->AddLine( ImVec2( player_bounds.min_x , player_bounds.min_y ) , ImVec2( player_bounds.min_x , player_bounds.min_y + corner_size ) , col , thickness );

	drawlist->AddLine( ImVec2( player_bounds.max_x , player_bounds.min_y ) , ImVec2( player_bounds.max_x - corner_size , player_bounds.min_y ) , col , thickness );
	drawlist->AddLine( ImVec2( player_bounds.max_x , player_bounds.min_y ) , ImVec2( player_bounds.max_x , player_bounds.min_y + corner_size ) , col , thickness );

	drawlist->AddLine( ImVec2( player_bounds.min_x , player_bounds.max_y ) , ImVec2( player_bounds.min_x + corner_size , player_bounds.max_y ) , col , thickness );
	drawlist->AddLine( ImVec2( player_bounds.min_x , player_bounds.max_y ) , ImVec2( player_bounds.min_x , player_bounds.max_y - corner_size ) , col , thickness );

	drawlist->AddLine( ImVec2( player_bounds.max_x , player_bounds.max_y ) , ImVec2( player_bounds.max_x - corner_size , player_bounds.max_y ) , col , thickness );
	drawlist->AddLine( ImVec2( player_bounds.max_x , player_bounds.max_y ) , ImVec2( player_bounds.max_x , player_bounds.max_y - corner_size ) , col , thickness );
}


void skeleton(ImDrawList* drawlist, uintptr_t mesh, const ImColor& col, float thickness)
{
	const std::vector<std::pair<int, int>> bone_pairs = {
		{110, 66}, {66, 7}, {7, 9}, {7, 38}, {9, 10}, {38, 39},
		{10, 11}, {39, 40}, {7, 2}, {2, 78}, {2, 71}, {78, 79},
		{79, 82}, {82, 83}, {71, 72}, {72, 75}, {75, 76}
	};

	for (const auto& pair : bone_pairs)
	{
		auto bone_a_index = pair.first;
		auto bone_b_index = pair.second;

		auto bone_a = bones::get_bone_position(mesh, bone_a_index);
		auto bone_b = bones::get_bone_position(mesh, bone_b_index);

		auto bone_a_screen = world_to_screen::project_to_screen(bone_a);
		auto bone_b_screen = world_to_screen::project_to_screen(bone_b);

		drawlist->AddLine(ImVec2(bone_a_screen.x, bone_a_screen.y), ImVec2(bone_b_screen.x, bone_b_screen.y), col, 1);
	}
}
