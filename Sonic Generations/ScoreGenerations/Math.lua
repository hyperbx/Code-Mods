function math.round(num)
	return math.floor(num + 0.5)
end

function math.sign(num)  
	if num > 0 then
		num = 1
	elseif num < 0 then
		num = -1
	else 
		num = 0
	end

	return num
end

function math.clamp(num, min, max)
	if num < min then
		num = min
	elseif num > max then
		num = max    
	end
	
	return num
end

function math.lerp(from, to, t)
	return from + (to - from) * math.clamp(t, 0, 1)
end

function math.isNaN(number)
	return not (number == number)
end