function GameHelpInit()

end

function GameHelpFrameMove()

--����ȭ�� ���ư��� ��ư
		
		if  5 < g_mouse.x and g_mouse.x < 55 and
		    5  < g_mouse.y and g_mouse.y < 45 then				
			if	g_mouse.e == KEY_DOWN then
				g_gamePhase = GAMEPHASE_BEGIN
			end	
		end

end


function GameHelpRender()
	Ltex.Draw(g_bg[5].dir, g_bg[5].x, g_bg[5].y)
end