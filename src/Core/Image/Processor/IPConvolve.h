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

#ifndef __IPCONVOLVE_H__
#define __IPCONVOLVE_H__

#include <string>
#include "Core/Image/Processor/ImageProcessorBase.h"
#include "Core/Utils/FilterKernel.h"

namespace degate
{
    /**
     * Processor: Convolve an image.
     */
    template <typename ImageTypeIn, typename ImageTypeOut>
    class IPConvolve : public ImageProcessorBase
    {
    private:
        FilterKernel_shptr kernel;

    public:

        /**
         * The constructor.
         */
        IPConvolve(FilterKernel_shptr kernel) :
            ImageProcessorBase("IPConvolve",
                               "Convolve an image.",
                               false,
                               typeid(typename ImageTypeIn::pixel_type),
                               typeid(typename ImageTypeOut::pixel_type)),
            kernel(kernel)
        {
        }

        /**
         * The destructor.
         */
        virtual ~IPConvolve()
        {
        }


        virtual ImageBase_shptr run(ImageBase_shptr in)
        {
            assert(in != nullptr);

            std::shared_ptr<ImageTypeIn> img_in = std::dynamic_pointer_cast<ImageTypeIn>(in);

            std::shared_ptr<ImageTypeOut> img_out(new ImageTypeOut(in->get_width(), in->get_height()));

            assert(img_in != nullptr);
            assert(img_out != nullptr);

            convolve<ImageTypeOut, ImageTypeIn>(img_out, img_in, kernel);

            return img_out;
        }
    };
}

#endif
