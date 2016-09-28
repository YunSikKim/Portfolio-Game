g_prav = 0
g_state = 0
g_spread = 0
g_switch = 0
g_movecount = 6
g_badcount = 0
cw = 0
ch = 0
flag = 0

function ReadMap(filename)
	local cnt=1
	f = io.open(filename, "r")
	
	while true do
		local n = f:read("*line")

		if nil == n then
			break
		end

		for w in string.gmatch(n, "([^,]+)") do
			g_field[cnt] = tonumber(w)
			cnt = cnt + 1
		end
	end

	f:close()
end

function GamePlayInit(alist)
	ReadMap("Stage" .. rnd .. ".csv")

	g_font[1] = Lfont.New("Rix계란후라이M.ttf", 16)
	g_font[2] = Lfont.New("Rix계란후라이M.ttf", 16)
	g_font[3] = Lfont.New("Rix계란후라이M.ttf", 25)

	-- InitCrash
	cw = 100
	ch = 100

	-- GetAni
	local cnt=1
	local i=1

	while true do
		local struct_tex = {dir=0, xrect=0, yrect=0, w=0, h=0, fme=0}

		if "" == alist[(i-1)*6+1] then
			break
		end

		struct_tex.dir = Ltex.New("Images/" .. alist[(i-1)*6+1])
		struct_tex.xrect = alist[(i-1)*6+2]
		struct_tex.yrect = alist[(i-1)*6+3]
		struct_tex.w = alist[(i-1)*6+4]
		struct_tex.h = alist[(i-1)*6+5]
		struct_tex.fme = alist[(i-1)*6+6]

		g_charAni[cnt] = struct_tex

		cnt = cnt + 1
		i = i + 1
	end
end

function GamePlayFrameMove()
	g_badcount = 0

	-- X-Box360
	if  5 < g_mouse.x and g_mouse.x < 55 and
	    5  < g_mouse.y and g_mouse.y < 45 then				
		if	g_mouse.e == KEY_DOWN then
			g_gamePhase = GAMEPHASE_BEGIN
			g_plus = 0
			g_movecount = 6
			rnd = 1
			ReadMap("Stage" .. rnd .. ".csv")
		end	
	end

	-- Game
	if 0 == flag then
		for i=1, #g_field do
			if 0 ~= g_field[i] and 1 == g_field[i] % 2 then -- 온순한 상태
				if g_field_xy[i*2-1] < g_mouse.x and g_field_xy[i*2-1]+cw > g_mouse.x and
				   g_field_xy[i*2] < g_mouse.y and g_field_xy[i*2]+ch > g_mouse.y and
				   KEY_DOWN == g_mouse.e and
				   g_state == 0 and
				   g_switch == 0 then
					g_field[i] = g_field[i] + 1
					g_state = g_field[i]
					g_prav = i
					g_switch = 1
					g_mouse.e = 0
				end
			elseif 0 ~= g_field[i] and 0 == g_field[i] % 2 then -- 분노한 상태
				if g_field_xy[i*2-1] < g_mouse.x and g_field_xy[i*2-1]+cw > g_mouse.x and
				   g_field_xy[i*2] < g_mouse.y and g_field_xy[i*2]+ch > g_mouse.y and
				   KEY_DOWN == g_mouse.e and
				   g_state == 0 and
				   g_switch == 0 then
					g_field[i] = g_field[i] - 1
					g_state = g_field[i]
					g_prav = i
					g_switch = 1
					g_mouse.e = 0
				end
			end

			if g_field[i] == 0 and g_prav ~= i and -- 이동
			   g_field_xy[i*2-1] < g_mouse.x and g_field_xy[i*2-1]+cw > g_mouse.x and
			   g_field_xy[i*2] < g_mouse.y and g_field_xy[i*2]+ch > g_mouse.y and
			   KEY_DOWN == g_mouse.e and
			   g_state ~= 0 and
			   g_switch == 1 then
				g_field[g_prav] = 0
				g_field[i] = g_state
				g_spread = g_state
				g_movecount = g_movecount -1
				g_plus = g_plus + 10
				g_switch = 2
			elseif g_prav == i and -- 선택 취소
				   g_field_xy[i*2-1] < g_mouse.x and g_field_xy[i*2-1]+cw > g_mouse.x and
				   g_field_xy[i*2] < g_mouse.y and g_field_xy[i*2]+ch > g_mouse.y and
				   KEY_DOWN == g_mouse.e and
				   g_state ~= 0 then
				    if 1 == g_state % 2 then
						g_field[i] = g_field[i] + 1
						g_state = 0
						g_switch = 0
					elseif 0 == g_state % 2 then
						g_field[i] = g_field[i] - 1
						g_state = 0
						g_switch = 0
					end
			end
				
			if 2 == g_switch and
			   g_field_xy[i*2-1] < g_mouse.x and g_field_xy[i*2-1]+cw > g_mouse.x and
			   g_field_xy[i*2] < g_mouse.y and g_field_xy[i*2]+ch > g_mouse.y and
			   KEY_DOWN == g_mouse.e then
				if 1 == g_field[i] % 2 then
					if g_spread + 1 == g_field[i-1] then
						if 1 ~= i % 5 then
							g_field[i-1] = g_spread
							g_plus = g_plus + 10
						end
					end
					if g_spread + 1 == g_field[i+1] then
						if 0 ~= i % 5 then
							g_field[i+1] = g_spread
							g_plus = g_plus + 10
						end
					end
					if g_spread + 1 == g_field[i-5] then
						if 1 <= i-5 then
							g_field[i-5] = g_spread
							g_plus = g_plus + 10
						end
					end
					if g_spread + 1 == g_field[i+5] then
						if 25 >= i+5 then
							g_field[i+5] = g_spread
							g_plus = g_plus + 10
						end
					end
				elseif 0 == g_field[i] % 2 then
					if g_spread - 1 == g_field[i-1] then
						if 1 ~= i % 5 then
							g_field[i-1] = g_spread
							g_plus = g_plus + 10
						end
					end
					if g_spread - 1 == g_field[i+1] then
						if 0 ~= i % 5 then
							g_field[i+1] = g_spread
							g_plus = g_plus + 10
						end
					end
					if g_spread - 1 == g_field[i-5] then
						if 1 <= i-5 then
							g_field[i-5] = g_spread
							g_plus = g_plus + 10
						end
					end
					if g_spread - 1 == g_field[i+5] then
						if 25 >= i+5 then
							g_field[i+5] = g_spread
							g_plus = g_plus + 10
						end
					end
				end

			g_state = 0
			g_switch = 0
			end
		end
	end

	if 0 >= g_movecount and 0 == flag then
		g_mouse.e = 0
		for s=1, #g_field do
			if g_field[s] ~= 0 and
			   0 == g_field[s] % 2 then
				flag = 1
			end
		end
	end
		
	if 1 == flag then
		if 183 < g_mouse.x and g_mouse.x < 300 and
		   500 < g_mouse.y and g_mouse.y < 530 and
		   KEY_DOWN == g_mouse.e then
			g_movecount = 6
			ReadMap("Stage" .. rnd .. ".csv")
			g_plus = 0
			flag = 0
		end
	elseif 0 >= g_movecount then
		g_gamePhase = GAMEPHASE_END
	end

	for i=1, #g_field do
	    if 0 ~= g_field[i] and
		   0 == g_field[i] % 2 then
			g_badcount = g_badcount + 1
		end
	end



	Lfont.Setup(g_font[1], "남은 횟수 : " .. g_movecount, 230, 705, "0xFF000000")
	Lfont.Setup(g_font[2], "분노 개수 : " .. g_badcount, 230, 738, "0xFF000000")
	Lfont.Setup(g_font[3], "다시하기", 183, 500, "0xFF000000")
end


function GamePlayRender()
	Ltex.Draw(g_bg[2].dir, g_bg[2].x, g_bg[2].y)

	-- DrawAni
	local tic = 300
	local timeCur = Lsys.GetTime()/tic

	if 5 >= rnd then
		Ltex.Draw(g_stage[1].dir, g_stage[1].x, g_stage[1].y)
	elseif 10 >= rnd then
		Ltex.Draw(g_stage[2].dir, g_stage[2].x, g_stage[2].y)
	elseif 15 >= rnd then
		Ltex.Draw(g_stage[3].dir, g_stage[3].x, g_stage[3].y)
	else
		Ltex.Draw(g_stage[4].dir, g_stage[4].x, g_stage[4].y)
	end

	if 10 > rnd then
		Ltex.Draw(g_number[rnd].dir, g_number[rnd].x, g_number[rnd].y)
	else
		Ltex.Draw(g_number[rnd].dir, g_number[rnd].x-6, g_number[rnd].y)
	end

	for i=1, #g_field do
		for j=1, #g_charAni do
			if j == g_field[i] then
				local struct_tex = g_charAni[j]
				local fidx = math.floor(timeCur) % struct_tex.fme + 1

				Ltex.Draw(struct_tex.dir, (fidx-1)*struct_tex.w, 0, fidx*struct_tex.w, struct_tex.h, g_field_xy[i*2-1]+struct_tex.xrect, g_field_xy[i*2]+struct_tex.yrect)
			end
		end
	end

	if 1 == flag then
		Ltex.Draw(g_bg[4].dir, 40, 200)
		Lfont.Draw(g_font[3])
	end

	for i=1, 2 do
		Lfont.Draw(g_font[i])
	end
end