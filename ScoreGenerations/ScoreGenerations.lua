function calculateGenerationsTimeBonus()

	-- Penalty for D rank.
	if (elapsedTime > secondsForC) then
		for i = (elapsedTime - secondsForC) / 20, 0, -1
		do
			elapsedTime = elapsedTime - 10
		end
	end
	
	return math.clamp(elapsedTime * 10, 0, 999999)
end