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

#ifndef __GATELIBRARYIMPORTER_H__
#define __GATELIBRARYIMPORTER_H__

#include "Globals.h"
#include "GateLibrary.h"
#include "Core/XML/XMLImporter.h"

#include <stdexcept>

namespace degate
{
    /**
     * The GateLibraryImporter imports a gate library. That is the file
     * gate_library.xml from your degate project.
     */
    class GateLibraryImporter : public XMLImporter
    {
    private:

        GateLibrary_shptr parse_gate_library_element(QDomElement const gl_element,
                                                     std::string const& directory);

        void parse_gate_templates_element(QDomElement const gate_templates_element,
                                          GateLibrary_shptr gate_lib,
                                          std::string const& directory);


        void parse_template_images_element(QDomElement const template_images_element,
                                           GateTemplate_shptr gate_tmpl,
                                           std::string const& directory);

        void parse_template_implementations_element(QDomElement const implementations_element,
                                                    GateTemplate_shptr gate_tmpl,
                                                    std::string const& directory);


        void parse_template_ports_element(QDomElement const template_ports_element,
                                          GateTemplate_shptr gate_tmpl,
                                          GateLibrary_shptr gate_lib);

    public:
        GateLibraryImporter()
        {
        }

        ~GateLibraryImporter()
        {
        }

        GateLibrary_shptr import(std::string const& filename);
    };
}
#endif
