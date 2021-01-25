// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreAreas.h"

ACoreAreas::ACoreAreas() {

}

void ACoreAreas::SetOutlineColor(int32 ColorOutline) {
}
void ACoreAreas::OnLineTraced(AChel* Player) {
}
void ACoreAreas::PickUpEventServer(AChel* Player) {
}
bool ACoreAreas::PickUpEventClient(AChel* Player) {
	return false;
}
bool ACoreAreas::PickUpEventReleaseClient(AChel* Player) {
	return false;
}
void ACoreAreas::PickUpEventReleaseServer(AChel* Player) {

}