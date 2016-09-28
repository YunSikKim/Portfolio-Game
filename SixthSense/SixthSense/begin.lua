function InitMouse()
	g_mouse.x, g_mouse.y = Lin.MousePos()
	g_mouse.e = Lin.MouseEvnt()
end

function GameBeginInit(blist, belist, slist, nlist)
	local cnt=1
	local i=1

	for i=1, #blist do -- bg_list
		local struct_tex = {dir=0, x=0, y=0}

		struct_tex.dir = Ltex.New("Images/" .. blist[i])

		g_bg[i] = struct_tex
	end

	for i=1, #slist do -- stage_list
		local struct_tex = {dir=0, x=8, y=159}

		struct_tex.dir = Ltex.New("Images/" .. slist[i])

		g_stage[i] = struct_tex
	end

	for i=1, #nlist do -- number_list
		local struct_tex = {dir=0, x=220, y=94}

		struct_tex.dir = Ltex.New("Images/" .. nlist[i])

		g_number[i] = struct_tex
	end

	while true do
		local struct_tex = {dir=0, x=0, y=0}

		if "" == belist[(i-1)*3+1] then
			break
		end

		struct_tex.dir = Ltex.New("Images/" .. belist[(i-1)*3+1])
		struct_tex.x = belist[(i-1)*3+2]
		struct_tex.y = belist[(i-1)*3+3]

		g_begin[cnt] = struct_tex

		cnt = cnt + 1
		i = i + 1
	end
end

function GameBeginFrameMove()
	if 130 < g_mouse.x and g_mouse.x < 345 and
	   420 < g_mouse.y and g_mouse.y < 470 then
		if g_mouse.e == KEY_DOWN then
		   g_gamePhase = GAMEPHASE_PLAY
		end
	end
	--help
	if 150 < g_mouse.x and g_mouse.x < 320 and
	   500 < g_mouse.y and g_mouse.y < 550 then
		if g_mouse.e == KEY_DOWN then
		   g_gamePhase = GAMEPHASE_HELP
		end
	end
	--Á¾·á
	if 150 < g_mouse.x and g_mouse.x < 320 and
	   580 < g_mouse.y and g_mouse.y < 630 then	
		if g_mouse.e == KEY_DOWN then
		   g_gamePhase	= GAMEPHASE_EXIT		-- exit		
		end
	end
end -- Lua_FrameMove

function GameBeginRender()
	Ltex.Draw(g_bg[1].dir, g_bg[1].x, g_bg[1].y)

	for i=1, #g_begin do
		Ltex.Draw(g_begin[i].dir, g_begin[i].x, g_begin[i].y)
	end	
end



