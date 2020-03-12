/* -----------------------------------------------------------------------------

PicoModel Library

Copyright (c) 2002, Randy Reddig & seaw0lf
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list
of conditions and the following disclaimer.

Redistributions in binary form must reproduce the above copyright notice, this
list of conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.

Neither the names of the copyright holders nor the names of its contributors may
be used to endorse or promote products derived from this software without
specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------- */

#if (!defined MDC_NORMAL_TABLE_INCLUDED)
#define MDC_NORMAL_TABLE_INCLUDED

/* mdc decoding normal table */
float mdcNormals[ 256 ][ 3 ] =
{
    { 1.000000f, 0.000000f, 0.000000f },
    { 0.980785f, 0.195090f, 0.000000f },
    { 0.923880f, 0.382683f, 0.000000f },
    { 0.831470f, 0.555570f, 0.000000f },
    { 0.707107f, 0.707107f, 0.000000f },
    { 0.555570f, 0.831470f, 0.000000f },
    { 0.382683f, 0.923880f, 0.000000f },
    { 0.195090f, 0.980785f, 0.000000f },
    { -0.000000f, 1.000000f, 0.000000f },
    { -0.195090f, 0.980785f, 0.000000f },
    { -0.382683f, 0.923880f, 0.000000f },
    { -0.555570f, 0.831470f, 0.000000f },
    { -0.707107f, 0.707107f, 0.000000f },
    { -0.831470f, 0.555570f, 0.000000f },
    { -0.923880f, 0.382683f, 0.000000f },
    { -0.980785f, 0.195090f, 0.000000f },
    { -1.000000f, -0.000000f, 0.000000f },
    { -0.980785f, -0.195090f, 0.000000f },
    { -0.923880f, -0.382683f, 0.000000f },
    { -0.831470f, -0.555570f, 0.000000f },
    { -0.707107f, -0.707107f, 0.000000f },
    { -0.555570f, -0.831469f, 0.000000f },
    { -0.382684f, -0.923880f, 0.000000f },
    { -0.195090f, -0.980785f, 0.000000f },
    { 0.000000f, -1.000000f, 0.000000f },
    { 0.195090f, -0.980785f, 0.000000f },
    { 0.382684f, -0.923879f, 0.000000f },
    { 0.555570f, -0.831470f, 0.000000f },
    { 0.707107f, -0.707107f, 0.000000f },
    { 0.831470f, -0.555570f, 0.000000f },
    { 0.923880f, -0.382683f, 0.000000f },
    { 0.980785f, -0.195090f, 0.000000f },
    { 0.980785f, 0.000000f, -0.195090f },
    { 0.956195f, 0.218245f, -0.195090f },
    { 0.883657f, 0.425547f, -0.195090f },
    { 0.766809f, 0.611510f, -0.195090f },
    { 0.611510f, 0.766809f, -0.195090f },
    { 0.425547f, 0.883657f, -0.195090f },
    { 0.218245f, 0.956195f, -0.195090f },
    { -0.000000f, 0.980785f, -0.195090f },
    { -0.218245f, 0.956195f, -0.195090f },
    { -0.425547f, 0.883657f, -0.195090f },
    { -0.611510f, 0.766809f, -0.195090f },
    { -0.766809f, 0.611510f, -0.195090f },
    { -0.883657f, 0.425547f, -0.195090f },
    { -0.956195f, 0.218245f, -0.195090f },
    { -0.980785f, -0.000000f, -0.195090f },
    { -0.956195f, -0.218245f, -0.195090f },
    { -0.883657f, -0.425547f, -0.195090f },
    { -0.766809f, -0.611510f, -0.195090f },
    { -0.611510f, -0.766809f, -0.195090f },
    { -0.425547f, -0.883657f, -0.195090f },
    { -0.218245f, -0.956195f, -0.195090f },
    { 0.000000f, -0.980785f, -0.195090f },
    { 0.218245f, -0.956195f, -0.195090f },
    { 0.425547f, -0.883657f, -0.195090f },
    { 0.611510f, -0.766809f, -0.195090f },
    { 0.766809f, -0.611510f, -0.195090f },
    { 0.883657f, -0.425547f, -0.195090f },
    { 0.956195f, -0.218245f, -0.195090f },
    { 0.923880f, 0.000000f, -0.382683f },
    { 0.892399f, 0.239118f, -0.382683f },
    { 0.800103f, 0.461940f, -0.382683f },
    { 0.653281f, 0.653281f, -0.382683f },
    { 0.461940f, 0.800103f, -0.382683f },
    { 0.239118f, 0.892399f, -0.382683f },
    { -0.000000f, 0.923880f, -0.382683f },
    { -0.239118f, 0.892399f, -0.382683f },
    { -0.461940f, 0.800103f, -0.382683f },
    { -0.653281f, 0.653281f, -0.382683f },
    { -0.800103f, 0.461940f, -0.382683f },
    { -0.892399f, 0.239118f, -0.382683f },
    { -0.923880f, -0.000000f, -0.382683f },
    { -0.892399f, -0.239118f, -0.382683f },
    { -0.800103f, -0.461940f, -0.382683f },
    { -0.653282f, -0.653281f, -0.382683f },
    { -0.461940f, -0.800103f, -0.382683f },
    { -0.239118f, -0.892399f, -0.382683f },
    { 0.000000f, -0.923880f, -0.382683f },
    { 0.239118f, -0.892399f, -0.382683f },
    { 0.461940f, -0.800103f, -0.382683f },
    { 0.653281f, -0.653282f, -0.382683f },
    { 0.800103f, -0.461940f, -0.382683f },
    { 0.892399f, -0.239117f, -0.382683f },
    { 0.831470f, 0.000000f, -0.555570f },
    { 0.790775f, 0.256938f, -0.555570f },
    { 0.672673f, 0.488726f, -0.555570f },
    { 0.488726f, 0.672673f, -0.555570f },
    { 0.256938f, 0.790775f, -0.555570f },
    { -0.000000f, 0.831470f, -0.555570f },
    { -0.256938f, 0.790775f, -0.555570f },
    { -0.488726f, 0.672673f, -0.555570f },
    { -0.672673f, 0.488726f, -0.555570f },
    { -0.790775f, 0.256938f, -0.555570f },
    { -0.831470f, -0.000000f, -0.555570f },
    { -0.790775f, -0.256938f, -0.555570f },
    { -0.672673f, -0.488726f, -0.555570f },
    { -0.488725f, -0.672673f, -0.555570f },
    { -0.256938f, -0.790775f, -0.555570f },
    { 0.000000f, -0.831470f, -0.555570f },
    { 0.256938f, -0.790775f, -0.555570f },
    { 0.488725f, -0.672673f, -0.555570f },
    { 0.672673f, -0.488726f, -0.555570f },
    { 0.790775f, -0.256938f, -0.555570f },
    { 0.707107f, 0.000000f, -0.707107f },
    { 0.653281f, 0.270598f, -0.707107f },
    { 0.500000f, 0.500000f, -0.707107f },
    { 0.270598f, 0.653281f, -0.707107f },
    { -0.000000f, 0.707107f, -0.707107f },
    { -0.270598f, 0.653282f, -0.707107f },
    { -0.500000f, 0.500000f, -0.707107f },
    { -0.653281f, 0.270598f, -0.707107f },
    { -0.707107f, -0.000000f, -0.707107f },
    { -0.653281f, -0.270598f, -0.707107f },
    { -0.500000f, -0.500000f, -0.707107f },
    { -0.270598f, -0.653281f, -0.707107f },
    { 0.000000f, -0.707107f, -0.707107f },
    { 0.270598f, -0.653281f, -0.707107f },
    { 0.500000f, -0.500000f, -0.707107f },
    { 0.653282f, -0.270598f, -0.707107f },
    { 0.555570f, 0.000000f, -0.831470f },
    { 0.481138f, 0.277785f, -0.831470f },
    { 0.277785f, 0.481138f, -0.831470f },
    { -0.000000f, 0.555570f, -0.831470f },
    { -0.277785f, 0.481138f, -0.831470f },
    { -0.481138f, 0.277785f, -0.831470f },
    { -0.555570f, -0.000000f, -0.831470f },
    { -0.481138f, -0.277785f, -0.831470f },
    { -0.277785f, -0.481138f, -0.831470f },
    { 0.000000f, -0.555570f, -0.831470f },
    { 0.277785f, -0.481138f, -0.831470f },
    { 0.481138f, -0.277785f, -0.831470f },
    { 0.382683f, 0.000000f, -0.923880f },
    { 0.270598f, 0.270598f, -0.923880f },
    { -0.000000f, 0.382683f, -0.923880f },
    { -0.270598f, 0.270598f, -0.923880f },
    { -0.382683f, -0.000000f, -0.923880f },
    { -0.270598f, -0.270598f, -0.923880f },
    { 0.000000f, -0.382683f, -0.923880f },
    { 0.270598f, -0.270598f, -0.923880f },
    { 0.195090f, 0.000000f, -0.980785f },
    { -0.000000f, 0.195090f, -0.980785f },
    { -0.195090f, -0.000000f, -0.980785f },
    { 0.000000f, -0.195090f, -0.980785f },
    { 0.980785f, 0.000000f, 0.195090f },
    { 0.956195f, 0.218245f, 0.195090f },
    { 0.883657f, 0.425547f, 0.195090f },
    { 0.766809f, 0.611510f, 0.195090f },
    { 0.611510f, 0.766809f, 0.195090f },
    { 0.425547f, 0.883657f, 0.195090f },
    { 0.218245f, 0.956195f, 0.195090f },
    { -0.000000f, 0.980785f, 0.195090f },
    { -0.218245f, 0.956195f, 0.195090f },
    { -0.425547f, 0.883657f, 0.195090f },
    { -0.611510f, 0.766809f, 0.195090f },
    { -0.766809f, 0.611510f, 0.195090f },
    { -0.883657f, 0.425547f, 0.195090f },
    { -0.956195f, 0.218245f, 0.195090f },
    { -0.980785f, -0.000000f, 0.195090f },
    { -0.956195f, -0.218245f, 0.195090f },
    { -0.883657f, -0.425547f, 0.195090f },
    { -0.766809f, -0.611510f, 0.195090f },
    { -0.611510f, -0.766809f, 0.195090f },
    { -0.425547f, -0.883657f, 0.195090f },
    { -0.218245f, -0.956195f, 0.195090f },
    { 0.000000f, -0.980785f, 0.195090f },
    { 0.218245f, -0.956195f, 0.195090f },
    { 0.425547f, -0.883657f, 0.195090f },
    { 0.611510f, -0.766809f, 0.195090f },
    { 0.766809f, -0.611510f, 0.195090f },
    { 0.883657f, -0.425547f, 0.195090f },
    { 0.956195f, -0.218245f, 0.195090f },
    { 0.923880f, 0.000000f, 0.382683f },
    { 0.892399f, 0.239118f, 0.382683f },
    { 0.800103f, 0.461940f, 0.382683f },
    { 0.653281f, 0.653281f, 0.382683f },
    { 0.461940f, 0.800103f, 0.382683f },
    { 0.239118f, 0.892399f, 0.382683f },
    { -0.000000f, 0.923880f, 0.382683f },
    { -0.239118f, 0.892399f, 0.382683f },
    { -0.461940f, 0.800103f, 0.382683f },
    { -0.653281f, 0.653281f, 0.382683f },
    { -0.800103f, 0.461940f, 0.382683f },
    { -0.892399f, 0.239118f, 0.382683f },
    { -0.923880f, -0.000000f, 0.382683f },
    { -0.892399f, -0.239118f, 0.382683f },
    { -0.800103f, -0.461940f, 0.382683f },
    { -0.653282f, -0.653281f, 0.382683f },
    { -0.461940f, -0.800103f, 0.382683f },
    { -0.239118f, -0.892399f, 0.382683f },
    { 0.000000f, -0.923880f, 0.382683f },
    { 0.239118f, -0.892399f, 0.382683f },
    { 0.461940f, -0.800103f, 0.382683f },
    { 0.653281f, -0.653282f, 0.382683f },
    { 0.800103f, -0.461940f, 0.382683f },
    { 0.892399f, -0.239117f, 0.382683f },
    { 0.831470f, 0.000000f, 0.555570f },
    { 0.790775f, 0.256938f, 0.555570f },
    { 0.672673f, 0.488726f, 0.555570f },
    { 0.488726f, 0.672673f, 0.555570f },
    { 0.256938f, 0.790775f, 0.555570f },
    { -0.000000f, 0.831470f, 0.555570f },
    { -0.256938f, 0.790775f, 0.555570f },
    { -0.488726f, 0.672673f, 0.555570f },
    { -0.672673f, 0.488726f, 0.555570f },
    { -0.790775f, 0.256938f, 0.555570f },
    { -0.831470f, -0.000000f, 0.555570f },
    { -0.790775f, -0.256938f, 0.555570f },
    { -0.672673f, -0.488726f, 0.555570f },
    { -0.488725f, -0.672673f, 0.555570f },
    { -0.256938f, -0.790775f, 0.555570f },
    { 0.000000f, -0.831470f, 0.555570f },
    { 0.256938f, -0.790775f, 0.555570f },
    { 0.488725f, -0.672673f, 0.555570f },
    { 0.672673f, -0.488726f, 0.555570f },
    { 0.790775f, -0.256938f, 0.555570f },
    { 0.707107f, 0.000000f, 0.707107f },
    { 0.653281f, 0.270598f, 0.707107f },
    { 0.500000f, 0.500000f, 0.707107f },
    { 0.270598f, 0.653281f, 0.707107f },
    { -0.000000f, 0.707107f, 0.707107f },
    { -0.270598f, 0.653282f, 0.707107f },
    { -0.500000f, 0.500000f, 0.707107f },
    { -0.653281f, 0.270598f, 0.707107f },
    { -0.707107f, -0.000000f, 0.707107f },
    { -0.653281f, -0.270598f, 0.707107f },
    { -0.500000f, -0.500000f, 0.707107f },
    { -0.270598f, -0.653281f, 0.707107f },
    { 0.000000f, -0.707107f, 0.707107f },
    { 0.270598f, -0.653281f, 0.707107f },
    { 0.500000f, -0.500000f, 0.707107f },
    { 0.653282f, -0.270598f, 0.707107f },
    { 0.555570f, 0.000000f, 0.831470f },
    { 0.481138f, 0.277785f, 0.831470f },
    { 0.277785f, 0.481138f, 0.831470f },
    { -0.000000f, 0.555570f, 0.831470f },
    { -0.277785f, 0.481138f, 0.831470f },
    { -0.481138f, 0.277785f, 0.831470f },
    { -0.555570f, -0.000000f, 0.831470f },
    { -0.481138f, -0.277785f, 0.831470f },
    { -0.277785f, -0.481138f, 0.831470f },
    { 0.000000f, -0.555570f, 0.831470f },
    { 0.277785f, -0.481138f, 0.831470f },
    { 0.481138f, -0.277785f, 0.831470f },
    { 0.382683f, 0.000000f, 0.923880f },
    { 0.270598f, 0.270598f, 0.923880f },
    { -0.000000f, 0.382683f, 0.923880f },
    { -0.270598f, 0.270598f, 0.923880f },
    { -0.382683f, -0.000000f, 0.923880f },
    { -0.270598f, -0.270598f, 0.923880f },
    { 0.000000f, -0.382683f, 0.923880f },
    { 0.270598f, -0.270598f, 0.923880f },
    { 0.195090f, 0.000000f, 0.980785f },
    { -0.000000f, 0.195090f, 0.980785f },
    { -0.195090f, -0.000000f, 0.980785f },
    { 0.000000f, -0.195090f, 0.980785f }
};

#endif // !! MDC_NORMAL_TABLE_INCLUDED
