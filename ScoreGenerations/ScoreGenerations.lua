function calculateTimeBonus()
	if (elapsedTime < minSeconds) then
		for i = minSeconds - elapsedTime, 0, -1
		do
			-- For every second above the minimum required bonus time, add 10 points.
			elapsedTime = elapsedTime + 10
		end
		
		-- Multiply bonus by 10.
		elapsedTime = elapsedTime * 10
	elseif (elapsedTime < maxSeconds) then
		for i = (maxSeconds - elapsedTime) / 10, 0, -1
		do
			-- For every 10 seconds above the maximum allowed bonus time, add 10 points.
			elapsedTime = elapsedTime + 10
		end
	else
		-- Fuck you.
		elapsedTime = 0
	end
	
	return math.clamp(elapsedTime, 0, scoreLimit)
end