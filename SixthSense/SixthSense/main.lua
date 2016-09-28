-- 위상
GAMEPHASE_BEGIN	= 1
GAMEPHASE_CHOICE	= 2
GAMEPHASE_PLAY		= 3
GAMEPHASE_HELP		= 4
GAMEPHASE_END		= 5
GAMEPHASE_OVER		= 6
GAMEPHASE_FINISH	= 7
GAMEPHASE_EXIT		= 480

-- 키
KEY_DOWN	= 1
KEY_UP	= 2
KEY_PRESS	= 3

-- 변수
bg_list = {}
ani_list = {}
begin_list = {}
number_list = {}
stage_list = {}

--------------------------------------------------------------------------------
-- game data -------------------------------------------------------------------
g_gamePhase = 1
rnd = 1
g_point = 0
g_total = 0
g_plus = 0
g_begin = {}
g_bg = {}
g_stage = {}
g_charAni = {}
g_field = {}
g_number = {}
--mouse

g_mouse		= {x=0, y=0, e=0, x1=0, y1=0}

--------------------------------------------------------------------------------
-- rendering and system data ---------------------------------------------------


-- font
g_font		= {}


---load file
Lsys.DoFile("begin.lua")
Lsys.DoFile("play.lua")
Lsys.DoFile("help.lua")
Lsys.DoFile("end.lua")
Lsys.DoFile("finish.lua")

g_window =
{
	x = 1,
	y = 1,
	w = 480,
	h = 800,
	cls = "Six-Sense v0.1",
	full = 0
}

g_field_xy =
{
	3,   160, -- 1
	97,  160,
	191, 160,
	283, 160,
	375, 160,
	3,   261, -- 2
	97,  261,
	191, 261,
	283, 261,
	375, 261,
	3,   362, -- 3
	97,  362,
	191, 362,
	283, 362,
	375, 362,
	3,   464, -- 4
	97,  464,
	191, 464,
	283, 464,
	375, 464,
	3,   567, -- 5
	97,  567,
	191, 567,
	283, 567,
	375, 567,
}

--------------------------------------------------------------------------------
-- setup the game system -------------------------------------------------------
function Lua_Create()
	Lsys.ScriptFile(1, "main.lua")

	Lsys.CreateWindow(
					 g_window.x,
				 	 g_window.y,
					 g_window.w,
					 g_window.h,
					 g_window.cls,
					 g_window.full
				   )

	Lsys.SetClearColor("0xFFFFFFFF")
	Lsys.ShowCursor(0)
	Lsys.ShowState(1)
	return 0
end -- Lua_Create



--------------------------------------------------------------------------------
-- Initialize ... --------------------------------------------------------------
function Lua_Init()
	bg_list =
	{
		"title.png",	
		"stage.png",	
		"clear.png",
		"gameover.png",
		"howto.png",
		"choice.png"
	}

	number_list =
	{
		"1.png",
		"2.png",
		"3.png",
		"4.png",
		"5.png",
		"6.png",
		"7.png",
		"8.png",
		"9.png",
		"10.png",
		"11.png",
		"12.png",
		"13.png",
		"14.png",
		"15.png",
		"16.png",
		"17.png",
		"18.png",
		"19.png",
		"20.png",
		"21.png",
		"22.png",
		"23.png",
		"24.png",
		"25.png",
		"26.png",
		"27.png",
		"28.png",
		"29.png",
		"30.png"
	}
	
	stage_list =
	{
		"orange.png",
		"pink.png",
		"blue.png",
		"brown.png"
	}

	begin_list =
	{
		"logo.png", 35, 170,
		"start.png", 140, 420,
		"help.png", 160, 500,
		"end.png", 160, 580,
		""
	}

	ani_list = -- 파일이름, x조절, y조절, 넓이, 높이, 프레임수
	{
		"bh.png", 15, 1, 74, 96, 3,		-- 1
		"bb.png", 3, -7, 96, 106, 5,		-- 2
		"fh.png", 19, 10, 66, 75, 3,		-- 3
		"fb.png", 0, 5, 102, 88, 3,		-- 4
		"eh.png", 6, 15, 90, 84, 2,		-- 5
		"eb.png", 2, -18, 100, 117, 4,	-- 6
		"gh.png", 16, 8, 71, 88, 2,		-- 7
		"gb.png", 3, 5, 98, 90, 3,		-- 8
		""
	}	
	
	GameBeginInit(bg_list, begin_list, stage_list, number_list)
	GamePlayInit(ani_list)
	GameHelpInit()
	GameEndInit()
	GameFinishInit()
	return 0
end -- Lua_Init


--------------------------------------------------------------------------------
-- Release ... -----------------------------------------------------------------
function Lua_Destroy()

	return 0
end -- Lua_Destroy



--------------------------------------------------------------------------------
-- Update data ... -------------------------------------------------------------
function Lua_FrameMove()
	InitMouse()

	if GAMEPHASE_BEGIN == g_gamePhase then
		GameBeginFrameMove()
	elseif GAMEPHASE_CHOICE == g_gamePhase then
		GameChoiceFrameMove()
	elseif GAMEPHASE_PLAY == g_gamePhase then
		GamePlayFrameMove()
	elseif GAMEPHASE_END == g_gamePhase then
		GameEndFrameMove()
	elseif GAMEPHASE_HELP == g_gamePhase then
		GameHelpFrameMove()
	elseif GAMEPHASE_FINISH == g_gamePhase then
		GameFinishFrameMove()
	elseif GAMEPHASE_EXIT == g_gamePhase then
		return -1
	end

	return 0
end



--------------------------------------------------------------------------------
-- Rendering ... ---------------------------------------------------------------
function Lua_Render()
	if GAMEPHASE_BEGIN == g_gamePhase then
		GameBeginRender()
	elseif GAMEPHASE_CHOICE == g_gamePhase then
		GameChoiceRender()
	elseif GAMEPHASE_PLAY == g_gamePhase then
		GamePlayRender()
	elseif GAMEPHASE_HELP == g_gamePhase then
		GameHelpRender()
	elseif GAMEPHASE_END == g_gamePhase then
		GameEndRender()
	elseif GAMEPHASE_OVER == g_gamePhase then
		GameOverRender()
	elseif GAMEPHASE_FINISH == g_gamePhase then
		GameFinishRender()
	end

	return 0
end -- Lua_Render

