function calculateTimeBonus()
  if 30000 - math.floor(elapsedTime) * 40 < 0 then
    return 0
  end
  
  return 30000 - math.floor(elapsedTime) * 40
end