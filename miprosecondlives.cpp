/*
 * Copyright 2012, 2013 Gauthier Legrand
 * Copyright 2012, 2013 Romuald Conty
 * 
 * This file is part of Minotor.
 * 
 * Minotor is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Minotor is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Minotor.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "miprosecondlives.h"

#include "minotor.h"

#include "minarandompixels.h"
#include "minaexpandingobjects.h"
#include "minaflash.h"
#include "minastars.h"
#include "minafallingobjects.h"
#include "minarotatingbars.h"

MiproSecondLives::MiproSecondLives(MinoProgramBank *bank) :
    MinoProgram(bank)
{
    this->setLabel("Vitalic - Second Lives");
    MinoAnimationGroup *agrp = new MinoAnimationGroup(this);
    MinaRandomPixels *arp = new MinaRandomPixels(agrp);
    arp->setColor(QColor::fromHslF(0.5, 1.0, 0.5));
    arp->setLoopSize("1");
    arp->setDensity(0.01);
    agrp->addAnimation(arp);
    this->addAnimationGroup(agrp);

    MinoAnimationGroup *ageo = new MinoAnimationGroup(this);
    MinaExpandingObjects *aeo = new MinaExpandingObjects(ageo);
    aeo->setColor(QColor::fromHslF(0.25, 1.0, 0.5));
    aeo->setLoopSize("8");
    aeo->setDuration("8");
    ageo->addAnimation(aeo);
    this->addAnimationGroup(ageo);

    MinoAnimationGroup *agf = new MinoAnimationGroup(this);
    MinaFlash *af = new MinaFlash(agf);
    af->setColor(QColor::fromHslF(0.6, 1.0, 0.5));
    af->setLoopSize("1");
    agf->addAnimation(af);
    this->addAnimationGroup(agf);

    MinoAnimationGroup *ags1 = new MinoAnimationGroup(this);
    MinaStars *as1 = new MinaStars(ags1);
    as1->setColor(QColor::fromHslF(0.65, 1.0, 0.5));
    as1->setLoopSize("1/4");
    as1->setDuration("2");
    as1->setDensity(0.5);
    ags1->addAnimation(as1);
    this->addAnimationGroup(ags1);

    MinoAnimationGroup *ags2 = new MinoAnimationGroup(this);
    MinaStars *as2 = new MinaStars(ags2);
    as2->setColor(QColor::fromHslF(0.8, 1.0, 0.5));
    as2->setLoopSize("1/4");
    as2->setDuration("2");
    as2->setDensity(0.5);
    ags2->addAnimation(as2);
    this->addAnimationGroup(ags2);

    MinoAnimationGroup *agf2 = new MinoAnimationGroup(this);
    MinaFlash *af2 = new MinaFlash(agf);
    af2->setColor(QColor::fromHslF(0.2, 1.0, 0.5));
    af2->setLoopSize("16");
    agf2->addAnimation(af2);
    this->addAnimationGroup(agf2);

    MinoAnimationGroup *agfo1 = new MinoAnimationGroup(this);
    MinaFallingObjects *afo1 = new MinaFallingObjects(agfo1);
    afo1->setColor(QColor::fromHslF(0.4, 1.0, 0.5));
    afo1->setLoopSize("1/2");
    afo1->setDirection("Left");
    afo1->setDensity(0.05);
    agfo1->addAnimation(afo1);
    this->addAnimationGroup(agfo1);

    MinoAnimationGroup *ags3 = new MinoAnimationGroup(this);
    MinaStars *as3 = new MinaStars(ags3);
    as3->setColor(QColor::fromHslF(0.4, 1.0, 0.5));
    as3->setLoopSize("1/4");
    as3->setDuration("2");
    as3->setDensity(0.5);
    ags3->addAnimation(as3);
    this->addAnimationGroup(ags3);

    MinoAnimationGroup *agfo2 = new MinoAnimationGroup(this);
    MinaFallingObjects *afo2 = new MinaFallingObjects(agfo2);
    afo2->setColor(QColor::fromHslF(0.6, 1.0, 0.5));
    afo2->setLoopSize("1/2");
    afo2->setDirection("Right");
    afo2->setDensity(0.05);
    agfo2->addAnimation(afo2);
    this->addAnimationGroup(agfo2);

    MinoAnimationGroup *agfo3 = new MinoAnimationGroup(this);
    MinaFallingObjects *afo3 = new MinaFallingObjects(agfo3);
    afo3->setColor(QColor::fromHslF(0.25, 1.0, 0.5));
    afo3->setLoopSize("8");
    afo3->setDuration(16);
    afo3->setDirection("Down");
    afo3->setDensity(0.2);
    agfo3->addAnimation(afo3);
    MinaFallingObjects *afo4 = new MinaFallingObjects(agfo3);
    afo4->setColor(1.0);
    afo4->setLoopSize("1/2");
    afo4->setDuration(2);
    afo4->setDirection("Up");
    afo4->setDensity(0.05);
    agfo3->addAnimation(afo4);
    this->addAnimationGroup(agfo3);

    MinoAnimationGroup *agrb1 = new MinoAnimationGroup(this);
    MinaRotatingBars *arb1 = new MinaRotatingBars(agrb1);
    arb1->setColor(QColor::fromHslF(0.6, 1.0, 0.5));
    arb1->setLoopSize("1");
    arb1->setWidth(0.25);
    arb1->setLength(0.65);
    arb1->setEasingCurveType(QEasingCurve::OutInBack);
    agrb1->addAnimation(arb1);
    this->addAnimationGroup(agrb1);
}
