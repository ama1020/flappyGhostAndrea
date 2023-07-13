#include "Population.h"
#include <stdlib.h>
#include <random>
#include <cstdint>
#include <fstream>

std::ofstream fout("result/copy_put.txt");

void Population::Init()
{
	for (int i = 0; i < nrdots; i++) {
		dots[i].Init();
	}
}

void Population::Draw(sf::RenderWindow& window) const
{
	for (int i = nrdots - 1; i >= 0; i--) {
		dots[i].Draw(window);
	}
}

void Population::Update(int score, float v)
{
	for (int i = 0; i < nrdots; i++) {
		if (dots[i].Update(score, v)) {
			dots[i].dead = true;
		}
	}
}

void Population::Dead(int i)
{
	dots[i].dead = true;
}

bool Population::AllDead()
{
	//It was type int
	for (int i = 0; i < nrdots; i++) {
		if (!dots[i].dead && !dots[i].reachedPosition) {
			return false;
		}
	}
	return true;

}

void Population::calculateFitness(int h)
{
	for (int i = 0; i < nrdots; i++) {
		dots[i].calculateFitness(h);
	}
}

void Population::calculateFitnessSum()
{
	for (int i = 0; i < nrdots; i++) {
		fitnessSum += dots[i].fitness;
	}
}

void Population::naturalSelection()
{
	calculateFitnessSum();
	SetBestDot();
	SelectParents();
	gen++;
}

void Population::mutate()
{
	for (int i = 1; i < nrdots; i++) {
		dots[i].brain.mutate(scorei);
	}
}

void Population::nextgen()
{
	for (int i = 0; i < nrdots; i++) {
		dots[i].Restart();
	}
}

void Population::SelectParents()
{
	std::ifstream fin("result/copy_in.txt"); //File: First line: k (index of Pressed where the bestDot is, he used it for the last jump)
											// Rest of lines: Press array
	int a = 2;
	int k1 = 0;
	int k = dots[bestdot].k;
	if (fin >> k1) { //read the value from fin into k1
		fin.close();
		if (k1 < k) { //If the k1 is less than the k: the bestDot has gone farest
			a = 1;
			std::ofstream fout("result/copy_in.txt");
			fout << k << '\n'; //We write the k value in the begining of the file
		}
	}
	else { //File doesnt exist
		fin.close();
		std::ofstream fout("result/copy_in.txt"); //We create it
		a = 0;
		fout << k << '\n'; //We write the k value
	}
	//Open the output file stream (fout) again in input, output, and append mode.
	std::ofstream fout("result/copy_in.txt", std::ios::in | std::ios::out | std::ios::ate);
	//Copy Press values from the best dot to the first dot 
	for (int i = 0; i < 20000; i++) {
		dots[0].brain.Press[i] = dots[bestdot].brain.Press[i];
		if (!a) { //It was a new file
			fout << dots[0].brain.Press[i] << ' '; //We write the Press value to fout
		}
		else if (a == 1) { //it was an existing file with a smaller k
			fout << dots[0].brain.Press[i] << ' ';
		}
	}
	fout.close();
	dots[0].isBest = true;
	dots[0].Init_Winner(); //It gets displayed yellow
	//Copy Press values from the best dot to all the other dots
	for (int i = 1; i < nrdots; i++)
		for (int j = 0; j < 20000; j++)
			dots[i].brain.Press[j] = dots[bestdot].brain.Press[j];
}

void Population::SetBestDot()
{
	float min = 10000.0f;
	int maxIndex = 0;
	for (int i = 0; i < nrdots; i++) {
		if ((float)(dots[i].fitness) < min) {
			min = (float)(dots[i].fitness);
			maxIndex = i;
		}
	}
	bestdot = maxIndex;
}

void Population::modifyscorei()
{
	for (int i = 0; i < nrdots; i++)
		if (!dots[i].dead) {
			int k1 = dots[i].k;
			if (k1 > scorei)
				scorei = k1;
			break;
		}
}

sf::Sprite Population::getSprite(int i)
{
	return dots[i].getSprite();
}

