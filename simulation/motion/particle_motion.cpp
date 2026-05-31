//
// Physics Simulation Program
// File: particle_motion.cpp
// Created by Tobias Sharman on 15/11/2025
//
// Description:
//   - Implementation of particle_motion.h
//

#include "simulation/motion/particle_motion.h"

#include "databases/particle-data/particle_database.h"
#include "particles/particle-types/atom.h"
#include "physics/fields/field_solver.h"
#include "physics/processes/continuous/particle_continuous_interactions.h"

void moveParticle(Particle& particle, const Quantity& dt, const Vector<3>& displacement) {
    if (auto* atom = dynamic_cast<Atom*>(&particle)) {
        if (const auto gamma = g_particleDatabase.getGyromagneticRatio(atom->getType())) {
            const auto magneticField = getFieldAtPoint(atom->getPosition());
            advancePolarisation(*atom, magneticField, *gamma, dt);
        }
    }

    const auto updatedPosition = particle.getPosition() + displacement;
    const auto updatedTime = particle.getTime() + dt;
    particle.setTime(updatedTime);
    particle.setPosition(updatedPosition);
}
