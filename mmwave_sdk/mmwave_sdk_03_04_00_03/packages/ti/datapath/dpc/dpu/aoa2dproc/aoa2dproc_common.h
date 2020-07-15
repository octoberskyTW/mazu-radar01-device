/**
 *   @file  aoa2dproc_common.h
 *
 *   @brief
 *      Implements Common definition across cfarcaProc DPU.
 *
 *  \par
 *  NOTE:
 *      (C) Copyright 2019 Texas Instruments, Inc.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

 /** @mainpage AOA2D AOA DPU using 2D angle FFT approach
 *
 *  @section aoa2d_dpu_intro_section AOA2D AOA DPU
 *
 * This DPU implements angle of arrival (AoA) estimation using 2D angle FFT approach
 * where 2D angle FFT is computed using HWA. This approach is applicable for TDM MIMO
 * scheme with virtual antennas arranged in two dimensional array where the number of
 * columns and rows are both greater than one.
 *
 * DPU generates information about detected objects into two lists: 1) list with coordinates
 * defined by @ref DPIF_PointCloudCartesian_t and 2) side information list defined by @ref DPIF_PointCloudSideInfo_t.
 * The DPU receives 1D-FFT Radar Cube matrix calculated by range processing DPU
 * and the list of detected objects (@ref DPIF_CFARDetList_t) which is assumed to
 * be populated by previous CFAR algorithm processing.\n\n
 *
 * @section hwa_aoa2d_section_HWA-AOA HWA-AOA-2D DPU (AoAProcHWA)
 *
 * This DPU implements angle of arrival (AoA) estimation using HWA and CPU.
 * A high level data flow is illustrated in figure below.
 *
 * @image html hwa_aoa2d_top_level.png "HWA-AOA using 2D angle FFT approach - high level data flow"
 *
 * For each detected object the processing
 * consists of the following:
 *  - Recalculation of 2D-FFT antenna symbols corresponding to the objects range/doppler index, computed by HWA.
 *  - Rx channel phase/gain compensation.
 *  - Doppler compensation and symbol mapping into 2D matrix as input to 2D angle FFT.
 *  - 2D-FFT calculation, computed by HWA.
 *  - Maximum peak search in the 2D FFT magnitude output, computed by HWA.
 *  - Peak grouping and selection of maximum peaks and X/Y/Z computation.
 *
 * The below figure depicts detailed DPU implementation.
 *
 * @image html hwa_aoa2d.png "HWA-AOA 2D angle FFT implementation (for 3 Tx antennas)"
 *
 * DPU processes data from the input CFAR detection list in a loop, two objects from the input list per loop.
 * The processing is done in ping/pong manner so that the HWA processing, the EDMA transfers and
 * the local core processing is done in parallel. Data processing is split in two paths,
 * ping and pong path, one detected object per path.
 * In each path processing is split between HWA and local core and it is divided in four stages:
 * 2D-FFT (Doppler FFT) calculation by HWA, Doppler compensation by local core,
 * 2D-FFT angle calculation and peak detection performed by HWA, and
 * peak selection, and XYZ estimation by local core. These four stages include:
 * 1. Calculation of the array of 2D-FFT Rx virtual antenna symbols as input to Azimuth FFT computation.
 *    1. Input EDMA pages from radarCube memory to HWA memory the 1D-FFT data corresponding to the range index
 *       of the detected object. Note the input size limiting condition:
 *       \f$N_{TxAnt}*N_{RxAnt}*N_{DopplerChirps}*sizeof(cmplx16ImRe\_t) \leq 16\;KB\f$
 *    2. HWA calculates 2D FFT. Note the output size limiting condition:
 *       \f$N_{TxAnt}*N_{RxAnt}*N_{DopplerBins}*sizeof(cmplx16ImRe\_t) \leq 32\;KB\f$
 *    3. Output EDMA  picks the data of the Doppler bin corresponding to the detected object's
 *       Doppler index from the above FFT output and copies into core local memory.
 * 2. CPU performs
 *    1. Rx channel phase/gain compensation
 *    2. Doppler compensation and symbol mapping into 2D matrix as input to 2D (azimuth/elevation) FFT.
 *       The diagram shows the input and output of symbol mapping corresponding to an example
 *       antenna pattern shown embedded near the output of the mapper.
 *    3. Triggers EDMA to copy data back to HWA memory
 * 3. 2D (azimuth/elevation) FFT calculation:
 *    1. EDMA (triggered from previous step) copies 2D-FFT antenna symbols from local memory to HWA memory.
 *    2. HWA calculates azimuth FFT (complex output).
 *    3. HWA calculates elevation FFT (complex output) on azimuth FFT outputs.
 *    4. HWA creates list of peaks as follows:
 *      1. When multi-object peak search is enabled, CFAR in HWA is run for each azimuth row
 *         to create a list of detected peaks.
 *      2. When multi-object peak search is disabled, statistics block in HWA is run for each
 *         azimuth row to create a list of peaks.
 *    5. EDMA copies HWA detected peaks from HWA memory to the local core memory.
 * 4. CPU selects the highest peak/peaks, and performs the final x/y/z calculation.
 *    The calculated data of detected objects are appended to the output lists.
 *
 * One HWA loop iteration processes 2 detected objects. If the number of detected objects is odd, a
 * dummy one is appended at the end of the list of detected points. It is processed by HWA, but at the
 * end not appended to the final list.
 *
 * The following figure shows the local core processing flow including two objects per loop.
 *
 * @image html hwa_aoa_flow_chart.png "Local core processing flow"
 *
 * The HWA runs in parallel with local core and EDMA transfers, processing data within its loop in the following order: ping path 2D-FFT, pong path 2D-FFT,
 * ping path 2D-azimuth/elevation FFT, pong path 2D-azimuth/elevation FFT.
 * This is illustrated in the timing diagram in figure below.
 *
 * @image html hwa_aoa_timing_diagram.png "Timing diagram example: processing 5 detected objects"
 *
 * The scheme uses four EDMA physical channels, two EDMA channels to input data from the
 * local core memory to HWA, one channel per path, and two EDMA channels to output data from
 * HWA memory to the local core memory, one EDMA channel per path. The scheme also uses 16 EDMA param
 * sets programmed for data transfer and HWA triggering. HWA programming is done by up to 14 HWA param sets.
 * The usage of EDMA and HWA param sets is described in the following two figures, the first of two showing
 * the usage when the multi-object peak detection is enabled, and the second of two,
 * when the multi-object peak detection is disabled.
 * Note the occurrence of the HWA dummy param, following the HWA CFAR param.
 * This is necessary because of the HWA register read issue, (the
 * register read is unreliable when the state machine is running), so the HWA dummy
 * param is inserted there to pause the HWA execution while the
 * register with the number of CFAR detections is read out by EDMA which immediately after the read
 * triggers the continuation of the HWA execution. In the case when multi-object peak detection
 * is disabled, the HWA dummy param has pure dummy role.
 * Note that EDMA input to HWA in the first stage is AB-Synchronized type transfer,
 * while all other EDMAs in the scheme are A-Synchronized type transfers. Since the
 * radar cube is aligned to 4 byte boundary, none of these transfers fall under the EDMA
 * 4K boundary problem.
 *
 * @image html hwa_aoa_param_sets.png "EDMA and HWA param set usage for multi peak detection mode"
 *
 * @image html hwa_aoa_param_sets_single_peak.png "EDMA and HWA param set usage for single peak detection mode"
 *
 * @subsection hwa_aoa2d_Azimuth_heat_map Azimuth heatmap preparation
 *    When the @ref DPU_AoAProc_DynamicLocalConfig::prepareRangeAzimuthHeatMap is enabled
 *    this DPU generates data for computing azimuth/elevation heat-map
 *    (e.g for visualization purposes). The exported data is a 2D array
 *    as x[number of range bins][number of virtual antennas] with elements being
 *    of type of type cmplx16ImRe_t. The elements are 2D FFT symbols corresponding
 *    to zero Doppler bin. The following figure depicts data generation for azimuth heat-map visualization.
 *    Here, as well, none of the transfers fall under the EDMA 4K boundary problem.
 *
 * @image html hwa_aoa_azimuth_heatmap.png "HWA-AOA implementation"
 *
 * @section hwa_aoa2d_api_section AoAProcHWA APIs
 *
 * - @ref DPU_AoAProcHWA_init - DPUs initialization function.
 * - @ref DPU_AoAProcHWA_config - DPUs configuration function. The configuration can only be done after
 *   the DPU has been initialized using @ref DPU_AoAProcHWA_init. If the parameters used by this DPU do not
 *   change from one frame to the next, this function can be called only once, for the first
 *   frame, otherwise it has to be called before each @ref DPU_AoAProcHWA_process.
 * - @ref DPU_AoAProcHWA_process - DPUs processing function performs AoA estimation of
 *   detected objects in the given frame. This processing can only be done after the
 *   DPU has been configured.
 * - @ref DPU_AoAProcHWA_control - DPUs control function. It processes following messages from DPC:
 *   - @ref DPU_AoAProcHWA_Cmd_FovAoACfg,
 *   - @ref DPU_AoAProcHWA_Cmd_MultiObjBeamFormingCfg,
 *   - @ref DPU_AoAProcHWA_Cmd_CompRxChannelBiasCfg,
 *   - @ref DPU_AoAProcHWA_Cmd_PrepareRangeAzimuthHeatMap,
 *   - @ref DPU_AoAProcHWA_Cmd_ExtMaxVelocityCfg
 *
 *  Full API details can be seen at @ref DPU_AOAPROC_EXTERNAL
 *
 *\n\n\n 
 *
 * @subsection hwa_aoa2d_Sect_Antenna_geometry Antenna Geometry Definition
 * Antenna geometry is defined by two arrays of structures of type @ref ANTDEF_AntOffset_t which hold the
 * antenna position offsets, in multiples of \f$ \lambda/2 \f$, in azimuth and elevation
 * direction. Antenna offsets for AoP and standard EVM boards is illustrated in figure below.
 * The AOP antenna geometry structures are defined in antenna_geometry.c.
 *
 * @image html antenna_geometries.png "Examples of antenna geometries"
 *
 * @subsection hwa_aoa2d_Sect_SymbolMapping_dopplerComp Symbol Mapping, Scaling and Doppler Compensation
 * Symbol mapping and Doppler compensation function  (@ref AoAProcHWA_dopplerCompensation) is performed by local core after
 * the Rx channel phase/gain compensation.
 *
 * @subsubsection hwa_aoa2d_Sect_SymbolMapping Symbol Mapping
 *  The 2D FFT antenna symbols are mapped into 2D matrix whose size and shape
 *  depend on the order and the number of tx antennas used in TDM MIMO scheme.
 *  The following configurations are supported: 4Rx/3Tx, 4Rx/2Tx, and 4Rx/1Tx
 *  with any Tx antenna order. Figure below shows example of antenna mapping.
 *
 * @image html ant_mapping_to_angle_fft_input.png "Antenna mapping to angle 2D-FFT input matrix"
 *
 * @subsubsection hwa_aoa2d_Sect_Scaling Scaling
 *  The automatic scaling is introduced because of the HWA
 *  CFAR peak grouping issue in xwr18xx device: the peak grouping feature within HWA CFAR will fail
 *  to export the valid peak when it consists of 2 or more consecutive identical
 *  samples at the peak position.
 *  When the signal level is small, the magnitude of the
 *  2D-FFT output is also small, and since the 2D output surface is smooth, the chance is increased
 *  that the output values around the peak position will have the same value, and the peak would be missed.
 *  Because of this issue, a gain is applied to the input symbols to reduce the
 *  chance of two identical consecutive values at the peak position. The gain is calculated by
 *  function @ref AoAProcHWA_3DFFTGainCalc such that the input symbols have averaged rms value of 1000. With this input level,
 *  the chance of missing peaks is reduced. Note this peak grouping issue is fixed in HWA for xwr68xx ES2.0 device but 
 *  the algorithm here is common across devices and does automatic scaling regardless of the device/HWA version.
 * 
 *
 * @subsubsection hwa_aoa2d_Sect_dopplerComp Doppler Compensation
 *  Doppler compensation is compensation for the Doppler phase shift on
 *    virtual Rx antenna symbols. In case of 2Tx TDM MIMO scheme, the second
 *    set of Rx symbols is rotated by half of the estimated Doppler phase shift.
 *    The estimated Doppler phase shift is the phase shift between subsequent
 *    chirps corresponding to the same Tx antenna. In case of 3Tx TDM MIMO scheme, the second
 *    set of Rx symbols is rotated by 1/3 of the estimated Doppler phase shift, while the third set
 *    of Rx symbols is rotated by 2/3 of the estimated Doppler phase shift. Refer to figure below.
 *    Note that the 2D antenna array is viewed from sensor towards the scene.
 *    @anchor hwa_aoa2d_Figure_doppler
 *    @image html doppler_compensation.png "Figure_doppler: Doppler Compensation"
 *
 * @subsection hwa_aoa2d_Sect_Peak_detection Peak selection in 2D azimuth/elevation FFT Output
 *
 * The azimuth/elevation angle estimation is based on the finding of the peak position,
 * azimuth index and elevation index, in the 2D angle FFT magnitude output.
 * The 2D FFT is computed by HWA using the same size (@ref DPU_AOAPROCHWA_NUM_ANGLE_BINS) in
 * azimuth and elevation direction. The peak search is implemented by combined
 * search by HWA and local core. Two approaches are implemented:
 * - When multi-object peak detection is disabled, peak search by HWA statistics
 *   block followed by local core processing.
 * - When multi-object peak detection is enabled, peak search by HWA CFAR followed
 *   by local core processing.
 *
 * In both approaches, HWA produces the initial list of detected peaks from 2D FFT output,
 * and then the local core completes the peak search and outputs the the final
 * list of detected peaks. The final number of detected peaks per range/Doppler
 * index pair is limited to
 * @ref DPU_AOAPROCHWA_MAX_NUM_EXPORTED_TARGETS_PER_RANGE_DOPPLER_PT.
 *
 * @subsubsection hwa_aoa2d_Sect_HWA_Max_Peak_Search Maximum peak search using HWA statistics block
 *
 * When multi-object peak detection is disabled, (when
 * @ref DPU_AoAProc_DynamicLocalConfig::multiObjBeamFormingCfg is disabled),
 * the HWA calculates the peak index in azimuth direction for every elevation bin.
 * The output is a list of length @ref DPU_AOAPROCHWA_NUM_ANGLE_BINS with elements
 * defined by @ref DPU_AoAProcHWA_HwaMaxOutput_t, where the element's field
 * maxInd represents the azimuth index position of the maximum peak, while the
 * element's index in the list represents the elevation position of the peak.
 *
 * The local core then searches for the maximum
 * peak in the list, @ref AoAProcHWA_findSinglePeak and produces the azimuth/elevation
 * index pair of the maximum peak in the 2D FFT output.
 *
 * @subsubsection hwa_aoa2d_Sect_CFAR_Max_Peak_Search Maximum peaks search using HWA CFAR
 *
 * When multi-object peak detection is enabled, the HWA CFAR engine is used to create
 * initial list of peaks, defined by @ref DPU_AoAProcHWA_CfarDetOutput_t .
 * The CFAR runs in azimuth direction for every elevation bin producing few
 * peaks per elevation bin. The relevant CFAR configuration parameters are:
 * - detection threshold = 1,
 * - guard length = 0,
 * - noise window = 2,
 * - noise shift = 2 (average of 4 neighbor samples)
 * - circular search is enabled,
 * - peak grouping is enabled,
 * - CFAR runs in azimuth direction, iterating in elevation direction,
 * - Detected peaks are exported in the output detection list
 *   @ref DPU_AoAProcHWA_CfarDetOutput_t where the field cellidx represents
 *   azimuth index, and the field iterNum represents elevation index.
 *
 * Figure below illustrates CFAR running along one azimuth line shown in red on the
 * 2D FFT output surface. The middle figure shows the cell under test (CUT) and
 * the noise. The figure on the right shows the difference between CUT and noise.
 * Since the threshold is set to 1, all cells with the difference greater than
 * zero will be detected by CFAR, but with the peak grouping enabled, only 3
 * peaks are reported by CFAR (black circles in the middle figure).
 * The complete output detection list of peaks is illustrated in figure below,
 * with detected peaks shown in red. Note that since the number of input FFT
 * symbols is not more than 4, and the FFT size being 64, no more than 4 peaks
 * would be expected per row.
 *
 *
 * @image html cfar_peak_search.png "Example: Peak search using HWA CFAR"
 *
 * Figure below illustrates all CFAR detected peaks in the example above.
 *
 * @image html angle_2dfft_and_cfar_peaks.png "Example: Peak search using HWA CFAR showing all CFAR detected peaks"
 *
 * @subsubsection hwa_aoa2d_Sect_Peak_Grouping Peak grouping on the local core
 *
 * When multi-object detection per range/Doppler bin is enabled, the peak grouping on
 * the local core is performed by two functions:
 *  - @ref AoAProcHWA_peakGrouping,
 *  - @ref AoAProcHWA_SelectMaxPeaks
 *
 * When multi-object detection per range/doppler bin is disabled, the maximum peak
 * selection is performed by
 *  - @ref AoAProcHWA_findSinglePeak
 *
 * The peak grouping function @ref AoAProcHWA_peakGrouping performs additional
 * peak grouping on the CFAR list of detected peaks. It eliminates neighboring
 * peaks occurring in the CFAR consecutive iterations and selects only the highest
 * peaks. Also at the end, besides the maximum peak, it eliminates any peak below
 * specified threshold relative to the maximum peak. The algorithm scans the CFAR
 * detected list @ref DPU_AoAProcHWA_CfarDetOutput_t and for each detected peak it
 * forms a kernel of size 5x5, fills the kernel with peaks from the input list, and
 * it qualifies the peak if it is greater than all the peaks found in the kernel.
 * The kernel size could have been set to 3x3, but because of the HWA peak grouping issue 
 * in xwr18xx (bug fixed in xwr68xx ES2.0), it is set to 5x5 to avoid breaking the 
 * sequences of neighboring peaks. 
 * The function outputs the number of selected peaks, and the index list of selected peaks
 * pointing to the input list. The size of output index list is limited to
 * @ref DPU_AOAPROCHWA_MAX_NUM_GROUPED_TARGETS_PER_RANGE_DOPPLER_PT .
 *
 * In the example above, the peak grouping function would initially select only
 * 7 peaks, labeled A to G in the figure above. Notice that the sequences of peaks
 * circularly wrap around in azimuth or elevation direction. At the end, the
 * highest peak, labeled A, along with any other peaks greater than the provided
 * threshold will be marked in the output list.
 *
 * The selection of N highest peaks is performed by @ref AoAProcHWA_SelectMaxPeaks .
 * This function sorts the selected peaks and copies the specified number of highest
 * peaks to the output list of type @ref DPU_AoAProcHWA_CfarDetOutput.
 * The number highest peaks is set by
 * @ref DPU_AOAPROCHWA_MAX_NUM_EXPORTED_TARGETS_PER_RANGE_DOPPLER_PT .
 *
 * When multi peak grouping is is disabled, the function @ref AoAProcHWA_findSinglePeak
 * searches for the maximum peak in the list of peaks provided by HWA statistics module.
 * The input list is of type @ref DPU_AoAProcHWA_HwaMaxOutput_t. The length of the
 * list is equal to elevation FFT size @ref DPU_AOAPROCHWA_NUM_ANGLE_BINS. The function
 * searches for the single maximum peak, constructs the azimuth and elevation index and fills
 * the maximum peak data to the output list of type @ref DPU_AoAProcHWA_CfarDetOutput_t.
 *
 *
 * @subsection hwa_aoa2d_dataXYZ Data Path - Direction of Arrival Estimation (x,y,z)
 *    The (x,y,z) coordinate computation per detected object is performed by @ref AoAProcHWA_XYZestimationAoA2D.
 *    The function also eliminates the objects outside of the specified azimuth and elevation field of view.
 *    \anchor hwa_aoa2d_Figure_geometry
 *    @image html coordinate_geometry.png "Figure A: Coordinate Geometry"
 *    \n
 *    \anchor hwa_aoa2d_Figure_wz
 *    @image html coordinate_geometry_wz.png "Figure wz"
 *    \n
 *    \anchor hwa_aoa2d_Figures_wx
 *    @image html coordinate_geometry_wx.png "Figures wx"
 *    \ref hwa_aoa2d_Figure_geometry shows orientation of (x,y,z) axes with respect to the
 *    sensor/antenna positions. The objective is to estimate
 *    the (x,y,z) coordinates of each detected object.
 *    \f$w_x\f$ is the phase difference between consecutive receive antennas in
 *    azimuth direction of the FFT 2D input array and \f$w_z\f$ is the phase difference between
 *    consecutive receive antennas in elevation direction of the FFT 2D input array.
 *    The phases for each antenna are shown in the \ref hwa_aoa2d_Figure_doppler.
 *    We assume that the phase shifts due to Doppler are already compensated i.e. \f$\delta=0\f$.
 *    \ref hwa_aoa2d_Figure_wz shows that the distance AB which represents the relative distance
 *    between wavefronts intersecting consecutive antennas in elevation
 *    direction is \f$AB = \frac{\lambda}{2} \sin (\phi)\f$.
 *    Therefore \f$W_z = \frac{2\pi}{\lambda} \cdot AB\f$, therefore \f$W_z = \pi \sin (\phi)\f$.
 *    \ref hwa_aoa2d_Figures_wx show that distance CD which represents the relative distance between wavefronts intersecting consecutive
 *    antennas in azimuth direction is \f$CD = \frac{\lambda}{2} \sin (\theta) \cos (\phi)\f$ Therefore \f$w_x =  \frac{2\pi}{\lambda} \cdot CD\f$,
 *    therefore \f$w_x = \pi \sin (\theta) \cos (\phi)\f$.
 *
 *    If \f$k_{azim},k_{elev}\f$ is the index pair of the maximum peak in \f$N{\times}N\f$ 2D-FFT represented as
 *    signed indices in range \f$[-\frac{N}{2}, \frac{N}{2}-1]\f$, then \f$ w_x \f$ will be
 *       \f[
 *            w_x = \frac{2\pi}{N}k_{azim}
 *       \f]
 *
 *    and
 *     \f[
 *       w_z= \frac{2\pi}{N}k_{elev}
 *     \f]
 *
 *    Calculate range (in meters) as:
 *       \f[
 *           R=k_r\frac{c \cdot F_{SAMP}}{2 \cdot S \cdot N_{FFT}}
 *       \f]
 *       where, \f$c\f$ is the speed of light (m/sec), \f$k_r\f$ is range index, \f$F_{SAMP}\f$ is the sampling frequency (Hz),
 *       \f$S\f$ is chirp slope (Hz/sec), \f$N_{FFT}\f$ is 1D FFT size.
 *    Based on above calculations of \f$R\f$, \f$w_x\f$ and \f$w_z\f$, the \f$(x,y,z)\f$ position of the object
 *    can be calculated as seen in the \ref hwa_aoa2d_Figure_geometry,
 *       \f[
 *           x = R\cos(\phi)\sin(\theta) = R\frac{w_x}{\pi}, \;\;\;\;\; z = R\sin(\phi) = R\frac{w_z}{\pi},\;\;\;\;\; y = \sqrt{R^2-x^2-z^2}
 *       \f]
 *    The computed \f$(x,y,z)\f$ along with the Doppler value for each detected object are populated in the output
 *    list, structured as @ref DPIF_PointCloudCartesian_t.
 *
 * @subsection hwa_aoa2d_fovSubSection Elimination of detected objects based on FoV limits
 *
 * The AoA DPU filters out detected objects whose azimuth, \f$\theta\f$, and elevation, \f$\phi\f$, angles
 * are not within configured FoV limits. The DPU receives the following FoV parameters:
 *
 * \f$\phi_{min},\;\phi_{max},\f$ - elevation angle FoV limits
 *
 * \f$\theta_{min},\;\theta_{max}\f$ - azimuth angle FoV limits
 *
 * The DPU computes \f$W_z\f$  and \f$W_x\f$ directly from azimuth FFT output data, where
 *
 * \f$W_z = w_z/\pi\f$
 *
 * \f$W_x = w_x/\pi\f$
 *
 * From equations in previous section the following holds
 *
 * \f$W_z = \sin(\phi)\f$
 *
 * \f$W_x = \cos(\phi)  \sin(\theta)\f$
 *
 * Because sine is a monotonic increasing function in the maximum possible range
 * of -90 deg, 90 deg, the elevation angle \f$\phi\f$ FoV limits can be checked on \f$W_z\f$
 * as follows
 *
 * \f[
 * \sin(\phi_{min}) \leq W_z \leq \sin(\phi_{max})
 * \f]
 *
 * Since \f$W_x\f$ is not monotonic in \f$\phi\f$ but monotonic on \f$\theta\f$,
 * the azimuth angle \f$\theta\f$ limits can be checked by checking \f$W_x\f$ after computing
 * the \f$\cos(\phi)\f$ on the measured \f$\phi\f$.
 *
 * \f[
 * \cos(\phi)\sin(\theta_{min}) \leq W_x \leq \cos(\phi) \sin(\theta_{max})
 * \f]
 *
 * where \f$\cos(\phi) = \sqrt{1 - \sin(\phi)^2} = \sqrt{1 - W_z^2}\f$.
 * Note that the terms  \f$\sin(\phi_{min})\f$, \f$\sin(\phi_{max})\f$,
 * \f$\sin(\theta_{min})\f$ and \f$\sin(\theta_{max})\f$ are precomputed during configuration time
 * and stored in the dpu's instance (@ref DPU_AoAProc_fovAoaLocalCfg_t) to be used
 * in the real-time limit checks above.
 * The brute-force method of checking limits on \f$\phi\f$ and \f$\theta\f$ directly
 * requires computing these, which involves two sin inverses, one cosine and one
 * division which are computationally more expensive than the above method.
 * 
 * 
 */

 
 
/** @defgroup DPU_AOAPROC_INTERNAL       aoaProc DPU Internal
 *
 */
/**
@defgroup DPU_AOAPROC_INTERNAL_FUNCTION            aoaProc DPU Internal Functions
@ingroup DPU_AOAPROC_INTERNAL
@brief
*   The section has a list of all internal API which are not exposed to the external
*   applications.
*/
/**
@defgroup DPU_AOAPROC_INTERNAL_DATA_STRUCTURE      aoaProc DPU Internal Data Structures
@ingroup DPU_AOAPROC_INTERNAL
@brief
*   The section has a list of all internal data structures which are used internally
*   by the aoaProc DPU module.
*/
/**
@defgroup DPU_AOAPROC_INTERNAL_DEFINITION          aoaProc DPU Internal Definitions
@ingroup DPU_AOAPROC_INTERNAL
@brief
*   The section has a list of all internal definitions which are used internally
*   by the aoaProc DPU.
*/
 
/** @defgroup DPU_AOAPROC_EXTERNAL       aoaProc DPU External
 */
/**
@defgroup DPU_AOAPROC_EXTERNAL_FUNCTION            aoaProc DPU External Functions
@ingroup DPU_AOAPROC_EXTERNAL
@brief
*   The section has a list of all the exported API which the user need to
*   invoke in order to use the aoaProc DPU
*/
/**
@defgroup DPU_AOAPROC_EXTERNAL_DATA_STRUCTURE      aoaProc DPU External Data Structures
@ingroup DPU_AOAPROC_EXTERNAL
@brief
*   The section has a list of all the data structures which are exposed to the user
*/
/**
@defgroup DPU_AOAPROC_EXTERNAL_DEFINITIONS      aoaProc DPU External Definitions
@ingroup DPU_AOAPROC_EXTERNAL
@brief
*   The section has a list of all the definitions which are exposed to the user
*/
/**
@defgroup DPU_AOAPROC_ERROR_CODE                   aoaProc DPU Error Codes
@ingroup DPU_AOAPROC_EXTERNAL
@brief
*   The section has a list of all the error codes which are generated by the sampleProc DPU
*/
 
/**************************************************************************
 *************************** Include Files ********************************
 **************************************************************************/
#ifndef AOA2DPROC_COMMON_H
#define AOA2DPROC_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

/* Standard Include Files. */
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

/*! @brief Converts Doppler index to signed variable. Value greater than or equal
 *         half the Doppler FFT size will become negative.
 */
#define AOA_DOPPLER_IDX_TO_SIGNED(_idx, _fftSize) ((_idx) < (_fftSize)/2 ? \
        ((int16_t) (_idx)) : ((int16_t) (_idx) - (int16_t) (_fftSize)))

/**
 * @brief Antenna offset position in vertical and horizontal directions
 *
 */
typedef struct DPU_AoAProc_AntOffset_t {
    /*! @brief  antenna offset in horizontal direction (azimuth) expressed in Lambda/2 */
    int16_t azimuthOffset;
    /*! @brief  antenna offset in vertical direction (elevation) expressed in Lambda/2 */
    int16_t elevationOffset;
} DPU_AoAProc_AntOffset;

/**
 * @brief Antenna offset positions in vertical and horizontal directions
 *
 */
typedef struct DPU_AoAProc_AntDef_t {
    /*! @brief  Tx antenna positions */
    DPU_AoAProc_AntOffset txAnt[SYS_COMMON_NUM_TX_ANTENNAS];
    /*! @brief  Rx antenna positions */
    DPU_AoAProc_AntOffset rxAnt[SYS_COMMON_NUM_RX_CHANNEL];
} DPU_AoAProc_AntDef;

/**
 * @brief
 *
 *
 */
typedef struct DPU_AoAProc_AntForwardLUT_t {
    /*! @brief  Antenna column index positions in lambda/2 */
    uint8_t     colIdx;
    /*! @brief  Antenna row index positions in lambda/2 */
    uint8_t     rowIdx;
} DPU_AoAProc_AntForwardLUT;

/**
 * @brief
 *  Field of view - AoA Configuration
 *
 * @details
 *  The structure contains the field of view - AoA configuration used in data path
 *
 *  \ingroup    DPU_AOAPROC_EXTERNAL_DATA_STRUCTURE
 *
 */
typedef struct DPU_AoAProc_FovAoaCfg_t
{
    /*! @brief    minimum azimuth angle (in degrees) exported to Host*/
    float        minAzimuthDeg;

    /*! @brief    maximum azimuth angle (in degrees) exported to Host*/
    float        maxAzimuthDeg;

    /*! @brief    minimum elevation angle (in degrees) exported to Host*/
    float        minElevationDeg;

    /*! @brief    maximum elevation angle (in degrees) exported to Host*/
    float        maxElevationDeg;
} DPU_AoAProc_FovAoaCfg;

/**
 * @brief
 *  Multi object beam forming Configuration
 *
 * @details
 *  The structure contains the Peak grouping configuration used in data path
 *
 *  \ingroup    DPU_AOAPROC_EXTERNAL_DATA_STRUCTURE
 *
 */
typedef struct DPU_AoAProc_MultiObjBeamFormingCfg_t
{
    /*! @brief    enabled flag:  1-enabled 0-disabled */
    uint8_t     enabled;

    /*! @brief    second peak detection threshold */
    float        multiPeakThrsScal;

} DPU_AoAProc_MultiObjBeamFormingCfg;

/**
 * @brief Range Bias and rx channel gain/phase compensation configuration.
 *
 *
 *  \ingroup    DPU_AOAPROC_EXTERNAL_DATA_STRUCTURE
 *
 */
typedef struct DPU_AoAProc_compRxChannelBiasCfg_t
{

    /*! @brief  Compensation for range estimation bias in meters */
    float rangeBias;

    /*! @brief  Compensation for Rx channel phase bias in Q15 format.
     *          The order here is like x[tx][rx] where rx order is 0,1,....SYS_COMMON_NUM_RX_CHANNEL-1
     *          and tx order is 0, 1,...,SYS_COMMON_NUM_TX_ANTENNAS-1 */
    cmplx16ImRe_t rxChPhaseComp[SYS_COMMON_NUM_TX_ANTENNAS * SYS_COMMON_NUM_RX_CHANNEL];

} DPU_AoAProc_compRxChannelBiasCfg;

/**
 * @brief
 *  Extended maximum velocity configuration
 *
 * @details
 *  Extended maximum velocity configuration
 *
 *  \ingroup    DPU_AOAPROC_EXTERNAL_DATA_STRUCTURE
 *
 */
typedef struct DPU_AoAProc_ExtendedMaxVelocityCfg_t
{
    /*! @brief    enabled flag:  1-enabled 0-disabled */
    uint8_t     enabled;

} DPU_AoAProc_ExtendedMaxVelocityCfg;

/**
 * @brief
 *  Static clutter removal configuration
 *
 * @details
 *  The structure contains the configuration for static clutter removal.
 *
 *  \ingroup DPU_AOAPROC_EXTERNAL_DATA_STRUCTURE
 */
typedef struct DPU_AoAProc_StaticClutterRemovalCfg_t
{
    /*! @brief Flag that indicates if static clutter removal is enabled.*/
    bool  isEnabled;
}DPU_AoAProc_StaticClutterRemovalCfg;

/**
 * @brief
 *  AoAProc dynamic configuration
 *
 * @details
 *  The structure is used to hold the dynamic configuration used for AoA
 *
 *  \ingroup    DPU_AOAPROC_EXTERNAL_DATA_STRUCTURE
 *
 */
typedef struct DPU_AoAProc_DynamicConfig_t
{

    /** @brief     Multiobject beam forming configuration */
    DPU_AoAProc_MultiObjBeamFormingCfg *multiObjBeamFormingCfg;

    /** @brief     Flag indicates to prepare data for azimuth heat-map */
    bool  prepareRangeAzimuthHeatMap;

    /** @brief     Pointer to Rx channel compensation configuration */
    DPU_AoAProc_compRxChannelBiasCfg *compRxChanCfg;

    /** @brief      Field of view configuration for angle of arrival */
    DPU_AoAProc_FovAoaCfg     *fovAoaCfg;

    /** @brief      Extended maximum velocity configuration */
    DPU_AoAProc_ExtendedMaxVelocityCfg *extMaxVelCfg;

    /*! @brief Static clutter removal configuration. Valid only for DSP version of the AoA DPU.*/
    DPU_AoAProc_StaticClutterRemovalCfg  staticClutterCfg;
} DPU_AoAProc_DynamicConfig;

/**
 * @brief
 *  Data processing Unit statistics
 *
 * @details
 *  The structure is used to hold the statistics of the DPU 
 *
 *  \ingroup DPU_AOAPROC_EXTERNAL_DATA_STRUCTURE
 */
typedef struct DPU_AoAProc_Stats_t
{
    /** @brief total processing time during all chirps in a frame excluding EDMA waiting time*/
    uint32_t            processingTime;

    /** @brief total wait time for EDMA data transfer during all chirps in a frame*/
    uint32_t            waitTime;
} DPU_AoAProc_Stats;

#ifdef __cplusplus
}
#endif

#endif 
