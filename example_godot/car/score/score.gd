extends Area2D

var cars = []

func _on_score_area_entered(area):
	if area.is_in_group("car") and !cars.has(area):
		area.score += 1
		cars.append(area)
