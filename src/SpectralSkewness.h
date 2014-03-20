/*
    MIR.EDU

    A vamp plug-in library for teaching MIR.
    Copyright (C) 2013-2014 Justin Salamon.

    This file is part of MIR.EDU

    MIR.EDU is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    MIR.EDU is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.


    Feature info:
 
    Feature name: Spectral Skewness
    Description: Compute the spectral skewness of each frame of the signal.
    If a frame is completely silent, a value of 0 is returned.
    Unit: none
    Formula: the third standardized moment:
    skewness = (sum( (f_i - c)^3 * m_i ) / sum (m_i))  /  (spread^3)
    where f_i are frequencies in Hz and m_i are their respective
    spectrak magnitudes, and c is the centroid given by:
    c = sum(f_i * m_i) / sum(m_i)
    and spread is the spectral spread (i.e. wieghted std. deviation) given
    by spread = sqrt( sum( (f_i - c)^2 * m_i ) / sum (m_i) )
    Reference:
 */

// Remember to use a different guard symbol in each header!
#ifndef _SPECTRALSKEWNESS_H_
#define _SPECTRALSKEWNESS_H_

#include <vector>
#include <cmath>
#include <ostream>
#include <vamp-sdk/Plugin.h>

using std::string;
using std::vector;
using std::cout;
using std::endl;

class SpectralSkewness : public Vamp::Plugin
{
public:
    SpectralSkewness(float inputSampleRate);
    virtual ~SpectralSkewness();

    string getIdentifier() const;
    string getName() const;
    string getDescription() const;
    string getMaker() const;
    int getPluginVersion() const;
    string getCopyright() const;

    InputDomain getInputDomain() const;
    size_t getPreferredBlockSize() const;
    size_t getPreferredStepSize() const;
    size_t getMinChannelCount() const;
    size_t getMaxChannelCount() const;

    ParameterList getParameterDescriptors() const;
    float getParameter(string identifier) const;
    void setParameter(string identifier, float value);

    ProgramList getPrograms() const;
    string getCurrentProgram() const;
    void selectProgram(string name);

    OutputList getOutputDescriptors() const;

    bool initialise(size_t channels, size_t stepSize, size_t blockSize);
    void reset();

    FeatureSet process(const float *const *inputBuffers,
                       Vamp::RealTime timestamp);

    FeatureSet getRemainingFeatures();

protected:
    // plugin-specific data and methods go here
    size_t m_blockSize;
    size_t m_stepSize;
};


#endif // _SPECTRALSKEWNESS_H_
