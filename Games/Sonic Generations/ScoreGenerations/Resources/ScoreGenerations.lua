function calculateTimeBonus()
	if (elapsedTime < minSeconds) then
		elapsedTime = (minSeconds - elapsedTime) * 100
	elseif (elapsedTime < maxSeconds) then	
		elapsedTime = (maxSeconds - elapsedTime) * 10
	else
		elapsedTime = 0
	end
	
	return math.clamp(elapsedTime, 0, scoreLimit)
end