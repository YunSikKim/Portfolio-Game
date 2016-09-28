g_finish = {}

function GameFinishInit()
	g_finish[1] = Lfont.New("Rix계란후라이M.ttf", 22)
	g_finish[2] = Lfont.New("Rix계란후라이M.ttf", 20)
end

function GameFinishFrameMove()
	if 200 < g_mouse.x and g_mouse.x < 317 and
	   680 < g_mouse.y and g_mouse.y < 710 and
	   KEY_DOWN == g_mouse.e then
	    g_movecount = 6
		rnd = 1
		ReadMap("Stage" .. rnd .. ".csv")
		g_gamePhase = GAMEPHASE_BEGIN
	end

	Lfont.Setup(g_finish[1], "최종 점수 : " .. g_total, 10, 100, "0xFF000000")
	Lfont.Setup(g_finish[2], "돌아가기", 200, 680, "0xFF000000")
end

function GameFinishRender()
	Ltex.Draw(g_bg[3].dir, g_bg[3].x, g_bg[3].y)

	for i=1, #g_finish do
		Lfont.Draw(g_finish[i])
	end
end