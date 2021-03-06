/**
 * This file is part of the IC reverse engineering tool Degate.
 *
 * Copyright 2008, 2009, 2010 by Martin Schobert
 * Copyright 2019-2020 Dorian Bachelot
 *
 * Degate is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * Degate is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with degate. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "Globals.h"
#include "SubProjectAnnotation.h"
#include <boost/format.hpp>

using namespace degate;

SubProjectAnnotation::SubProjectAnnotation(float min_x, float max_x, float min_y, float max_y,
                                           std::string const& subproject_path) :
    Annotation(min_x, max_x, min_y, max_y, Annotation::SUBPROJECT)
{
    set_path(subproject_path);
}

SubProjectAnnotation::SubProjectAnnotation(BoundingBox const& bbox,
                                           std::string const& subproject_path) :
    Annotation(bbox, Annotation::SUBPROJECT)
{
    set_path(subproject_path);
}

void SubProjectAnnotation::set_path(std::string const& subproject_path)
{
    Annotation::set_parameter("subproject-directory", subproject_path);
}

std::string SubProjectAnnotation::get_path() const
{
    return Annotation::get_parameter<std::string>("subproject-directory");
}
