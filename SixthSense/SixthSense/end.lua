g_result = {}

function GameEndInit()
	g_result[1] = Lfont.New("Rix계란후라이M.ttf", 25)
	g_result[2] = Lfont.New("Rix계란후라이M.ttf", 22)
	g_result[3] = Lfont.New("Rix계란후라이M.ttf", 22)
	g_result[4] = Lfont.New("Rix계란후라이M.ttf", 22)
	g_result[5] = Lfont.New("Rix계란후라이M.ttf", 22)
	g_result[6] = Lfont.New("Rix계란후라이M.ttf", 22)
	g_result[7] = Lfont.New("Rix계란후라이M.ttf", 20)
end

function GameEndFrameMove()
	if 330 < g_mouse.x and g_mouse.x < 447 and
	   600 < g_mouse.y and g_mouse.y < 630 and
	    KEY_DOWN == g_mouse.e then
		g_gamePhase = GAMEPHASE_PLAY
		rnd = rnd + 1
		
		g_plus = 0
		g_point = g_total
		
		if 31 == rnd then
			g_gamePhase = GAMEPHASE_FINISH
		else
			g_movecount = 6
			ReadMap("Stage" .. rnd .. ".csv")
		end
	end

	g_total = g_point + g_plus + (rnd*10)

	Lfont.Setup(g_result[1], rnd .. " Stage Result", 100, 150, "0xFF000000")
	Lfont.Setup(g_result[2], "기존 점수 : " .. g_point, 80, 250, "0xFF000000")
	Lfont.Setup(g_result[3], "추가 점수 : " .. g_plus, 80, 300, "0xFF000000")
	Lfont.Setup(g_result[4], "스테이지 점수 : " .. rnd*10, 80, 350, "0xFF000000")
	Lfont.Setup(g_result[5], "+ -------------------", 30, 400, "0xFF000000")
	Lfont.Setup(g_result[6], "총 점수 : " .. g_total, 80, 450, "0xFF000000")
	Lfont.Setup(g_result[7], "계속하기", 330, 600, "0xFF000000")
end

function GameEndRender()
	Ltex.Draw(g_bg[1].dir, g_bg[1].x, g_bg[1].y)

	for i=1, #g_result do
		Lfont.Draw(g_result[i])
	end
end
