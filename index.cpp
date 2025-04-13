#include "index.h"
#include <src/rendering/menu/wrapper.h>

std::string get_weapon_name(uintptr_t pawn_private)
{

	std::string weapon_name;
	uint64_t current_weapon = cmd::read<uint64_t>(pawn_private + 0xa80); //currentweapon
	uint64_t weapon_data = cmd::read<uint64_t>(current_weapon + 0x5e8); //weapondata
	uint64_t item_name = cmd::read<uint64_t>(weapon_data + 0x40);//itemname
	if (!item_name) return "No Weapon";

	uint64_t FData = cmd::read<uint64_t>(item_name + 0x18);
	int FLength = cmd::read<int>(item_name + 0x20);

	if (FLength > 0 && FLength < 50)
	{
		wchar_t* WeaponBuffer = new wchar_t[FLength];
		cmd::read_phy_mem_only((void*)FData, (PVOID)WeaponBuffer, FLength * sizeof(wchar_t));
		std::wstring wstr_buf(WeaponBuffer);
		weapon_name.append(std::string(wstr_buf.begin(), wstr_buf.end()));

		delete[] WeaponBuffer;
	}

	return weapon_name;
}

ImVec4 get_rank_color(int32_t Tier)
{

	if (Tier == 0 || Tier == 1 || Tier == 2)
		return ImVec4(0.902f, 0.580f, 0.227f, 1.0f); // Bronze
	else if (Tier == 3 || Tier == 4 || Tier == 5)
		return ImVec4(0.843f, 0.843f, 0.843f, 1.0f); // Silver
	else if (Tier == 6 || Tier == 7 || Tier == 8)
		return ImVec4(1.0f, 0.871f, 0.0f, 1.0f); // Gold
	else if (Tier == 9 || Tier == 10 || Tier == 11)
		return ImVec4(0.0f, 0.7f, 0.7f, 1.0f); // Platinum
	else if (Tier == 12 || Tier == 13 || Tier == 14)
		return ImVec4(0.0f, 0.0f, 0.7f, 1.0f); // Diamond
	else if (Tier == 15)
		return ImVec4(0.7f, 0.7f, 0.7f, 1.0f); // Elite
	else if (Tier == 16)
		return ImVec4(1.0f, 0.6f, 0.0f, 1.0f); // Champion
	else if (Tier == 17)
		return ImVec4(0.6f, 0.0f, 0.6f, 1.0f); // Unreal
	else
		return ImVec4(0.0f, 0.7859f, 1.0f, 1.0f); // Unranked
}

std::string get_rank(int32_t Tier)
{

	if (Tier == 0)
		return std::string("Bronze 1");
	else if (Tier == 1)
		return std::string("Bronze 2");
	else if (Tier == 2)
		return std::string("Bronze 3");
	else if (Tier == 3)
		return std::string("Silver 1");
	else if (Tier == 4)
		return std::string("Silver 2");
	else if (Tier == 5)
		return std::string("Silver 3");
	else if (Tier == 6)
		return std::string("Gold 1");
	else if (Tier == 7)
		return std::string("Gold 2");
	else if (Tier == 8)
		return std::string("Gold 3");
	else if (Tier == 9)
		return std::string("Platinum 1");
	else if (Tier == 10)
		return std::string("Platinum 2");
	else if (Tier == 11)
		return std::string("Platinum 3");
	else if (Tier == 12)
		return std::string("Diamond 1");
	else if (Tier == 13)
		return std::string("Diamond 2");
	else if (Tier == 14)
		return std::string("Diamond 3");
	else if (Tier == 15)
		return std::string("Elite");
	else if (Tier == 16)
		return std::string("Champion");
	else if (Tier == 17)
		return std::string("Unreal");
	else
		return std::string("Unranked");
}

inline std::wstring MBytesToWString(const char* lpcszString)
{
	int len = strlen(lpcszString);
	int unicodeLen = ::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, NULL, 0);
	wchar_t* pUnicode = new wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, (LPWSTR)pUnicode, unicodeLen);
	std::wstring wString = (wchar_t*)pUnicode;
	delete[] pUnicode;
	return wString;
}
inline std::string WStringToUTF8(const wchar_t* lpwcszWString)
{
	char* pElementText;
	int iTextLen = ::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, NULL, 0, NULL, NULL);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, (iTextLen + 1) * sizeof(char));
	::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, pElementText, iTextLen, NULL, NULL);
	std::string strReturn(pElementText);
	delete[] pElementText;
	return strReturn;
}

inline void DrawString3(float fontSize, int x, int y, ImVec4 color, bool bCenter, bool stroke, const char* pText, ...)
{
	ImU32 converted_color = ImGui::ColorConvertFloat4ToU32(color);
	va_list va_alist;
	char buf[1024] = { 0 };
	va_start(va_alist, pText);
	_vsnprintf_s(buf, sizeof(buf), pText, va_alist);
	va_end(va_alist);
	std::string text = WStringToUTF8(MBytesToWString(buf).c_str());
	if (bCenter)
	{
		ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
		x = x - textSize.x / 4;
		y = y - textSize.y;
	}
	if (stroke)
	{
		/*ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());*/
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), text.c_str());
	}
	ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y), converted_color, text.c_str());
}

void stroked_text(ImFont* font, float fontSize, ImVec2 position, ImColor color, const char* text)
{

	//MASK
	ImGui::GetForegroundDrawList()->AddText(font, fontSize, ImVec2(position.x - 1, position.y - 1), ImColor(0, 0, 0), text);
	ImGui::GetForegroundDrawList()->AddText(font, fontSize, ImVec2(position.x + 1, position.y - 1), ImColor(0, 0, 0), text);
	ImGui::GetForegroundDrawList()->AddText(font, fontSize, ImVec2(position.x - 1, position.y + 1), ImColor(0, 0, 0), text);
	ImGui::GetForegroundDrawList()->AddText(font, fontSize, ImVec2(position.x + 1, position.y + 1), ImColor(0, 0, 0), text);
	ImGui::GetForegroundDrawList()->AddText(font, fontSize, position, color, text);
}


std::wstring string_to_wstring(const std::string& str) {
	if (str.empty()) return std::wstring();
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	std::wstring wstr(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstr[0], size_needed);
	return wstr;
}

std::string wstring_to_utf8(const std::wstring& wstr) {
	if (wstr.empty()) return std::string();
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
	std::string str(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &str[0], size_needed, NULL, NULL);
	return str;
}


namespace updater {

	void run( )
	{
		while ( true )
		{
			auto uworld = cmd::read<uintptr_t>( virtualaddy + offsets::uworld );
			auto owning_game_instance = cmd::read<uintptr_t>( uworld + offsets::owning_game_instance );
			auto local_player = cmd::read<uintptr_t>(cmd::read<uintptr_t>( owning_game_instance + offsets::local_players ) );
			auto player_controller = cmd::read<uintptr_t>( local_player + offsets::player_controller );
			auto player_state = cmd::read<uintptr_t>( player_controller + offsets::player_state );
			auto local_pawn = cmd::read<uintptr_t>( player_controller + offsets::acknowledged_pawn );
			auto root_component = cmd::read<uintptr_t>( local_pawn + offsets::root_component );

			udata::world_t = {
				uworld,
				owning_game_instance,
				local_player,
				player_controller,
				player_state,
				local_pawn,
				root_component,
				cmd::read<int>( player_state + offsets::team_id )
			};

			auto game_state = cmd::read<uintptr_t>( uworld + offsets::game_state );
			auto player_array = cmd::read<numerics::tarray<uintptr_t>>( game_state + offsets::player_array ).get_all( );

			udata::world_t.game_state = game_state;
			udata::world_t.player_array = player_array;
		

			std::vector<udata::actor> actors;
			actors.reserve( player_array.size( ) );

			for ( const auto& player_state : player_array )
			{
				if ( !player_state ) continue;

				auto team_id = cmd::read<int>( player_state + offsets::team_id );

				auto pawn_private = cmd::read<uintptr_t>( player_state + offsets::pawn_private );
				if ( !pawn_private ) continue;

				if ( pawn_private == udata::world_t.local_pawn ) continue;

				auto mesh = cmd::read<uintptr_t>( pawn_private + offsets::mesh );
				if ( !mesh ) continue;

				auto character_movement = cmd::read<uintptr_t>( pawn_private + offsets::character_movement );
				if ( !character_movement ) continue;

				auto kill_score = cmd::read<int>( player_state + offsets::kill_score );

				auto current_weapon = cmd::read<uintptr_t>( pawn_private + offsets::current_weapon );

				actors.emplace_back( player_state , pawn_private , mesh , team_id , kill_score , character_movement , current_weapon );
			}

			udata::actor_t = std::move( actors );

			Sleep( 250 );
		}
	}
} // namespace updater

std::string get_player_name( uintptr_t playerState ) {
			auto Name = cmd::read<uintptr_t>( playerState + 0xb08);
			auto length = cmd::read<int>( Name + 0x10 );
			auto v6 = ( __int64 ) length;

			if ( length <= 0 || length > 255 ) return std::string( "BOT" );

			auto FText = ( uintptr_t ) cmd::read<__int64>( Name + 0x8 );
			
			wchar_t* Buffer = new wchar_t [ length ];
			
			cmd::read_phy_mem_only( reinterpret_cast< PVOID >( FText ) , Buffer , length * sizeof( wchar_t ) );

			char v21;
			int v22;
			int i;

			int v25;
			UINT16* v23;

			v21 = v6 - 1;
			if ( !( UINT32 ) v6 )
				v21 = 0;
			v22 = 0;
			v23 = ( UINT16* ) Buffer;
			for ( i = ( v21 ) & 3; ; *v23++ += i & 7 )
			{
				v25 = v6 - 1;
				if ( !( UINT32 ) v6 )
					v25 = 0;
				if ( v22 >= v25 )
					break;
				i += 3;
				++v22;
			}

			std::wstring PlayerName{ Buffer };
			delete[ ] Buffer;
			return std::string( PlayerName.begin( ) , PlayerName.end( ) );
		}

namespace visuals {
	void draw_actors( ImDrawList* drawlist ) {
		//ImGui::PushFont( interFont );
		camera::update_camera( );

		auto closest_distance = FLT_MAX;
		auto closest_actor = udata::actor( 0 );

		auto aspect_ratio = static_cast< float >( numerics::screen_width ) / numerics::screen_height;
		world_to_screen::inv_fov = tanf( camera::fov * static_cast< float >( std::numbers::pi ) / 360.0f ) / aspect_ratio;
		world_to_screen::rotation_matrix = matrix_operations::create_rotation_matrix( camera::rotation );

		for (auto& current_actor : udata::actor_t) {
			auto head = bones::get_bone_position(current_actor.mesh, 110);
			auto head_projected = world_to_screen::project_to_screen(head);
			auto root = bones::get_bone_position(current_actor.mesh, 0);
			auto root_projected = world_to_screen::project_to_screen(root);

			int box_height = abs(head_projected.y - head_projected.y);
			int box_width = static_cast<int>(box_height * 0.50f);
			float distance = camera::location.distance(root) / 100.0f;

			ImVec2 top_left(root_projected.x - box_width / 2, head_projected.y);
			ImVec2 bottom_right(root_projected.x + box_width / 2, root_projected.y);

			auto player_bounds = player::get_player_bounds(current_actor.mesh);


			if (visuals::boxes) {
				box(drawlist, player_bounds, ImColor(255, 0, 0), visuals::thickness);
			}
			if (visuals::corner_boxes) {
				cornered_box(drawlist, player_bounds, ImColor(255, 0, 0), visuals::corner_box_outlined, visuals::thickness);
			}
			if (visuals::distance) {
				char distance_string[64];
				sprintf_s(distance_string, "%.fm", distance);
				ImVec2 text_size = ImGui::CalcTextSize(distance_string);
				drawlist->AddText(ImVec2(root_projected.x - text_size.x / 2, root_projected.y - text_size.y / 2), ImColor(255, 255, 255), distance_string);
			}

			ImColor esp_col;
			ImColor box_fill_col;

			if (visuals::skeletonesp)
			{
				skeleton(drawlist, current_actor.mesh, ImColor(255, 255, 255), visuals::thickness);
			}


			if (visuals::username)
			{
				auto username = get_player_name(current_actor.player_state);
				auto username_to_text_size = ImGui::CalcTextSize(username.c_str()).x;

				
				auto root_x = (player_bounds.min_x + player_bounds.max_x) / 2.0f;
				auto root_y = player_bounds.max_y;

				
				ImVec2 text_position(root_x - username_to_text_size / 2, root_y - 15);

				
				drawlist->AddText(text_position, ImColor(255, 255, 255), username.c_str());
			}

			float YOffset = 0;

			if (visuals::rankesp)
			{
				uintptr_t habenero = cmd::read<uintptr_t>(current_actor.player_state + 0xa48); // https://dumpspace.spuckwaffel.com/Games/?hash=6b77eceb&type=classes&idx=AFortPlayerState&member=HabaneroComponent
				int32_t RankProgress = cmd::read<int32_t>(habenero + 0xd0 + 0x10);
				std::string ranktype = get_rank(RankProgress);
				std::wstring w_ranktype = string_to_wstring(ranktype);
				std::string final = wstring_to_utf8(w_ranktype);




				ImVec2 text_size = ImGui::CalcTextSize(final.c_str());
				YOffset = YOffset + 13;
				DrawString3(16, head_projected.x - (text_size.x / 2), head_projected.y - YOffset, get_rank_color(RankProgress), true, true, final.c_str());
			}

			float yOffset = 10.0f;
			if (visuals::weaponesp)
			{
				std::string weaponName = get_weapon_name(offsets::pawn_private);

				ImVec2 textSize = ImGui::CalcTextSize(weaponName.c_str());
				stroked_text(ImGui::GetFont(), 13.0f, ImVec2(head_projected.x - textSize.x / 2, head_projected.y + yOffset - textSize.y / 2), ImColor(255, 255, 255), weaponName.c_str());
			}


		}

		


	}
}