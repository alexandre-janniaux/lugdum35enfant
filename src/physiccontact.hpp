#pragma once


struct PhysicContact
{
	PhysicBody* first;
	PhysicBody* second;
	PhysicGeom* firstGeom;
	PhysicGeom* secondGeom;
};
