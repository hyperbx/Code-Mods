function math.round(in_value)
	return math.floor(in_value + 0.5)
end

function math.sign(in_value)  
	if in_value > 0 then
		in_value = 1
	elseif in_value < 0 then
		in_value = -1
	else 
		in_value = 0
	end

	return in_value
end

function math.clamp(in_value, in_min, in_max)
	if in_value < in_min then
		in_value = in_min
	elseif in_value > in_max then
		in_value = in_max    
	end
	
	return in_value
end

function math.lerp(in_from, in_to, in_time)
	return in_from + (in_to - in_from) * math.clamp(in_time, 0, 1)
end

function math.isNaN(in_value)
	return not (in_value == in_value)
end