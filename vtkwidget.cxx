#include "vtkwidget.h"
#include<vtkMarchingCubes.h>
#include<vtkPolyDataConnectivityFilter.h>
#include<vtkImageResample.h>
#include<vtkTIFFReader.h>
#include<vtk_tiff.h>
#include <math.h> 
#include <vtkGPUInfo.h>
#include <vtkGPUInfoList.h>
#include<vtkStringArray.h>
#include <vtkPointData.h>
#include<vtkImageAccumulate.h>
#include<QVector>
#include<vtkImageMagnitude.h>
#include<math.h>
#include<qprogressdialog.h>
#include<vtkImageAppend.h>
#include<vtkGlyph3DMapper.h>
#include<vtkGlyph3D.h>
#include<vtkArrowSource.h>
#include<vtkScalarBarActor.h>
#include <vtkSmoothPolyDataFilter.h>
#include <vtkTextProperty.h>
#include<vtkImageAppend.h>
#include<vtkBMPReader.h>
#include<vtkAbstractImageInterpolator.h>
#include<vtkOctreePointLocator.h>
#include<vtkBMPReader.h>
#include<vtkDICOMImageReader.h>

//vtkIdType vram;
double imgmax;
int vramvalue;


vtkwidget::vtkwidget(QWidget *parent) :
    QVTKWidget(parent)
{
    volpropchange = vtkSmartPointer<vtkImageChangeInformation>::New();

    readervti = vtkSmartPointer<vtkXMLImageDataReader>::New();

    readertiff = vtkSmartPointer<vtkTIFFReader> ::New();

    volume = vtkSmartPointer<vtkVolume>::New();

    leftRenderer = vtkSmartPointer<vtkRenderer>::New();

    mapper = vtkSmartPointer<vtkSmartVolumeMapper>::New();

	rcmapper = vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
	 
    volumeColor = vtkSmartPointer<vtkColorTransferFunction>::New();

    LightKit = vtkSmartPointer<vtkLightKit> ::New();

    volumeProperty = vtkSmartPointer<vtkVolumeProperty>::New() ;

    volumeScalarOpacity = vtkSmartPointer<vtkPiecewiseFunction>::New();

	volumeScalarOpacity1 = vtkSmartPointer<vtkPiecewiseFunction>::New();

	volumeScalarOpacity2 = vtkSmartPointer<vtkPiecewiseFunction>::New();

	volumeScalarOpacity3 = vtkSmartPointer<vtkPiecewiseFunction>::New();

    style = vtkSmartPointer <vtkInteractorStyleTrackballCamera>::New();

	volumeGradientOpacity = vtkSmartPointer<vtkPiecewiseFunction>::New();

	poly_mapper = vtkSmartPointer<vtkPolyDataMapper>::New();

	actor = vtkSmartPointer<vtkImageActor>::New();

	imseq = vtkSmartPointer<vtkTIFFReader>::New();

	//imgdata = vtkSmartPointer<vtkImageData>::New();

	dsmapper = vtkSmartPointer<vtkDataSetMapper>::New();

	input = vtkSmartPointer<vtkImageData>::New();

	reader = vtkSmartPointer<vtkAlgorithm>::New();

	widget = vtkSmartPointer<vtkOrientationMarkerWidget>::New();

	poly_actor = vtkSmartPointer<vtkActor>::New();

	

}

void vtkwidget::initialize(vtkImageData *input)
{

	leftRenderer->RemoveAllViewProps();

	//Set default light parameters
	leftRenderer->SetAutomaticLightCreation(1);
	/*
	LightKit->SetKeyLightWarmth(0.6); LightKit->SetKeyLightIntensity(0.75); LightKit->SetKeyLightElevation(50); LightKit->SetKeyLightAzimuth(10);
	LightKit->SetFillLightWarmth(0.40); LightKit->SetKeyToFillRatio(3); LightKit->SetFillLightElevation(-75); LightKit->SetFillLightAzimuth(-10);
	LightKit->SetBackLightWarmth(0.5); LightKit->SetKeyToBackRatio(3.5); LightKit->SetBackLightElevation(0); LightKit->SetBackLightAzimuth(110);
	LightKit->SetHeadLightWarmth(0.5); LightKit->SetKeyToHeadRatio(3);
	*/

	//Add Volume Gradient Opacity
	//vtkwid->volumeGradientOpacity->AddPoint(0,0);
	//vtkwid->volumeGradientOpacity->AddPoint(100,1);

	// The opacity transfer function is used to control the opacity
	// of different tissue types.



	// The color transfer function maps voxel intensities to colors.
	// It is modality-specific, and often anatomy-specific as well.
	// The goal is to one color for flesh (between 500 and 1000)
	// and another color for bone (1150 and over).



	mapper->SetAverageIPScalarRange(20, 255);

	//Adjust Rotation Style of Camera

	GetInteractor()->SetInteractorStyle(style);

	int ncol = input->GetNumberOfScalarComponents();
	//Set volumeProperty parameters
	if (ncol < 3 )
    {
		
		
		volumeColor->AddRGBPoint(0, 0, 0, 0);
        volumeColor->AddRGBPoint(imgmax, 1, 1, 1);

		volumeScalarOpacity->AddPoint(0, 0.00);
        volumeScalarOpacity->AddPoint(imgmax, 1.00);

		volumeProperty->SetColor(volumeColor);
		volumeProperty->SetScalarOpacity(volumeScalarOpacity);
		
	
    }
	
	else if (ncol= 3)

   {
	vtkSmartPointer <vtkColorTransferFunction> c1 = vtkSmartPointer<vtkColorTransferFunction>::New();
	c1->AddRGBPoint(0, 0, 0, 0);
    c1->AddRGBPoint(imgmax, 1, 0, 0);
	vtkSmartPointer <vtkColorTransferFunction> c2 = vtkSmartPointer<vtkColorTransferFunction>::New();

	c2->AddRGBPoint(0, 0, 0, 0);
    c2->AddRGBPoint(imgmax, 0, 1, 0);
	vtkSmartPointer <vtkColorTransferFunction> c3 = vtkSmartPointer<vtkColorTransferFunction>::New();

	c3->AddRGBPoint(0, 0, 0, 0);
    c3->AddRGBPoint(imgmax, 0, 0, 1);


	


	volumeProperty->SetColor(0,c1);
	volumeProperty->SetColor(1,c2);
	volumeProperty->SetColor(2,c3);


	volumeScalarOpacity1->AddPoint(0, 0.00);
    volumeScalarOpacity1->AddPoint(imgmax, 1.00);
	volumeScalarOpacity2->AddPoint(0, 0.00);
    volumeScalarOpacity2->AddPoint(imgmax, 1.00);
	volumeScalarOpacity3->AddPoint(0, 0.00);
    volumeScalarOpacity3->AddPoint(imgmax, 1.00);
	volumeProperty->SetScalarOpacity(0,volumeScalarOpacity1);
	volumeProperty->SetScalarOpacity(1,volumeScalarOpacity2);
	volumeProperty->SetScalarOpacity(2,volumeScalarOpacity3);

    }

	
	
	
	// volumeProperty->SetGradientOpacity(volumeGradientOpacity);
	//volumeProperty->SetInterpolationType(VTK_NEAREST_INTERPOLATION);
	//volumeProperty->ShadeOff();
	LightKit->AddLightsToRenderer(leftRenderer);
	mapper->SetInputData(input);
	

	input->RemoveAllObservers();

	render();

}

void vtkwidget::render()
{

	mapper->SetBlendModeToComposite();
    mapper->SetInteractiveAdjustSampleDistances(0);
	volumeProperty->SetInterpolationType(VTK_CUBIC_INTERPOLATION);
	//mapper->SetInputConnection(reader->GetOutputPort());

        //mapper->SetRequestedRenderModeToRayCast();
	//if (input->GetActualMemorySize() > 0.8*(mapper->GetMaxMemoryInBytes())/1024)
	//{
	//	mapper->SetRequestedRenderModeToRayCast();
	//}
	

	leftRenderer->ResetCamera();
	//mapper->SetInteractiveUpdateRate(2);
	
	//mapper->SetMaxMemoryFraction(0.5);
	volume->SetMapper(mapper);
	mapper->ReleaseDataFlagOn();
	volume->SetProperty(volumeProperty);
	
	// Add Volume to renderer
	//leftRenderer->SetUseDepthPeeling(1);
	//leftRenderer->SetMaximumNumberOfPeels(100);
	leftRenderer->AddVolume(volume);
	volume->SetOrigin(volume->GetCenter());
	//this->qvtkWidgetLeft->GetRenderWindow()->AddRenderer(leftRenderer);
	//   vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
	//     vtkSmartPointer<vtkRenderWindowInteractor>::New();
	// renderWindowInteractor->SetRenderWindow(qvtkWidgetLeft->GetRenderWindow());
	// VTK/Qt wedded

	
	// Render and interact
	//  vtkwid-> renderWindow->Render();
	// renderer->AutomaticLightCreationOn();
	//   vtkwid-> renderWindow->SetWindowName("Volume Viewer");
	//  vtkwid-> renderWindowInteractor->Start();
	GetRenderWindow()->AddRenderer(leftRenderer);
	this->show();
	// Set up axes widget
	


}


void vtkwidget::renderpoly()
{
	
	// Create a 3D model using marching cubes
	vtkSmartPointer<vtkMarchingCubes> mc =
		vtkSmartPointer<vtkMarchingCubes>::New();
	mc->SetInputConnection(readertiff->GetOutputPort());
	mc->ComputeNormalsOn();
	mc->ComputeGradientsOn();
	mc->SetValue(1, 100);
	
// second value acts as threshold

	// To remain largest region
	vtkSmartPointer<vtkPolyDataConnectivityFilter> confilter =
		vtkSmartPointer<vtkPolyDataConnectivityFilter>::New();
	confilter->SetInputConnection(mc->GetOutputPort());
	//confilter->SetExtractionModeToLargestRegion();
	//confilter->SetExtractionModeToAllRegions();



	//imageDataGeometryFilter->SetInputConnection(input->);
	//imageDataGeometryFilter->SetInputData(readertiff->GetOutput());
	//imageDataGeometryFilter->Update();

	vtkSmartPointer<vtkContourFilter> contour_filter = vtkSmartPointer<vtkContourFilter>::New();
	poly_mapper->SetInputConnection(confilter->GetOutputPort());
	
	//poly_mapper->SetColorModeToMapScalars();
	
	leftRenderer->RemoveAllViewProps();
	volume->Delete();
	vtkSmartPointer<vtkActor> poly_actor =
		vtkSmartPointer<vtkActor>::New();
	
	poly_actor->SetMapper(poly_mapper);
	leftRenderer->AddActor(poly_actor);
	GetRenderWindow()->AddRenderer(leftRenderer);
	GetInteractor()->Render();
	
	
}

void vtkwidget::renderpol(vtkPolyData *pol)
{
    /*
    // Create the tree
    vtkSmartPointer<vtkOctreePointLocator> octree =
      vtkSmartPointer<vtkOctreePointLocator>::New();
    octree->SetDataSet(pol);
    octree->BuildLocator();

    vtkSmartPointer<vtkPolyData> octpolyd =
      vtkSmartPointer<vtkPolyData>::New();
    octree->GenerateRepresentation(0,octpolyd);
    

	*/

	poly_mapper->SetInputData(pol);

	poly_mapper->SetColorModeToMapScalars();
	poly_actor->SetMapper(poly_mapper);
	poly_actor->GetProperty()->EdgeVisibilityOff();
	poly_actor->SetOrigin(poly_actor->GetCenter());


	vtkSmartPointer<vtkScalarBarActor> scalarBar = vtkSmartPointer<vtkScalarBarActor>::New();
	scalarBar->SetTitle("Inclination angle");
	scalarBar->SetNumberOfLabels(2);
	scalarBar->SetDisplayPosition(0, 0);
	scalarBar->SetHeight(0.0625);
	scalarBar->SetWidth(0.4);
	scalarBar->SetOrientationToHorizontal();


	vtkSmartPointer<vtkLookupTable> hueLut = vtkSmartPointer<vtkLookupTable>::New();
	hueLut->SetTableRange(-90, 90);
	hueLut->SetHueRange(0, 1);
	hueLut->SetSaturationRange(1, 1);
	hueLut->SetValueRange(1, 1);
	hueLut->SetRampToLinear();
	hueLut->Build();

	vtkSmartPointer<vtkLookupTable> belvinLUT = vtkSmartPointer<vtkLookupTable>::New();
	


	vtkSmartPointer<vtkColorTransferFunction> ctf =
		vtkSmartPointer<vtkColorTransferFunction>::New();
	belvinLUT->SetTableRange(0, 255);
	belvinLUT->SetRampToLinear();
	belvinLUT->SetHueRange(0, 1);
	belvinLUT->SetSaturationRange(1, 1);
	belvinLUT->SetValueRange(1, 1);
	belvinLUT->Build();


	scalarBar->SetLookupTable(hueLut);
	poly_mapper->SetScalarRange(0, 255);
	poly_mapper->ImmediateModeRenderingOn();
	poly_mapper->SetLookupTable(belvinLUT);
	leftRenderer->AddActor(poly_actor);
	leftRenderer->AddActor2D(scalarBar);
	GetRenderWindow()->AddRenderer(leftRenderer);
	GetInteractor()->Render();
	this->show();
	
	
}

void vtkwidget::renderactor(vtkImageData *img)
{
	vtkSmartPointer<vtkGlyph3D> glyph3D =
		vtkSmartPointer<vtkGlyph3D>::New();
	vtkSmartPointer<vtkPolyDataMapper> glyph3DMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	vtkSmartPointer<vtkArrowSource> arrowSource =
		vtkSmartPointer<vtkArrowSource>::New();

	vtkSmartPointer<vtkActor> glyph_actor =
		vtkSmartPointer<vtkActor>::New();
	glyph3D->SetSourceConnection(arrowSource->GetOutputPort());
	glyph3D->SetVectorModeToUseVector();
	glyph3D->SetInputData(img);
	glyph3D->SetScaleFactor(0.1);
	glyph3D->Update();

	glyph3DMapper->SetInputConnection(glyph3D->GetOutputPort());
	glyph_actor->SetMapper(glyph3DMapper);
	leftRenderer->AddActor(glyph_actor);
	GetRenderWindow()->AddRenderer(leftRenderer);
	GetInteractor()->Render();
	this->show();

}

void vtkwidget::setbg(double bg_r, double bg_g, double bg_b)
{
	leftRenderer->SetBackground(bg_r, bg_g, bg_b);
	GetRenderWindow()->Render();
}

void vtkwidget::setvram()
{
    //vram = 0.75* vramVal * 1024 * 1024;
   // mapper->SetMaxMemoryInBytes(vram);

	string line;
	ifstream vram("vram.info");
	if (vram.is_open())
	{
		while (getline(vram, line))
		{
			vramvalue = (atoi(line.c_str()))/1024;
			// ui->vram_val->setCurrentIndex((vramval/1024)-1);
		

		}
		vram.close();
	}

}

void vtkwidget::setdims(double dim_x,  double dim_y, double dim_z)
{
	volpropchange->SetInputData(mapper->GetInput());
    volpropchange->SetOutputSpacing(dim_x, dim_y, dim_z);
	volpropchange->Update();
	mapper->SetInputData(volpropchange->GetOutput());
	//leftRenderer->ResetCamera();
	//GetRenderWindow()->Render();
	render();
}

void vtkwidget::updatelights(double kw, double ki, double ke, double ka, double fw, double fkf, double fe, double fa, double bw, double bkb, double be, double ba, double hw, double hkh, bool shading)
{
	LightKit->SetKeyLightWarmth(kw); LightKit->SetKeyLightIntensity(ki); LightKit->SetKeyLightElevation(ke); LightKit->SetKeyLightAzimuth(ka);
	LightKit->SetFillLightWarmth(fw); LightKit->SetKeyToFillRatio(fkf); LightKit->SetFillLightElevation(fe); LightKit->SetFillLightAzimuth(fa);
	LightKit->SetBackLightWarmth(bw); LightKit->SetKeyToBackRatio(bkb); LightKit->SetBackLightElevation(be); LightKit->SetBackLightAzimuth(ba);
	LightKit->SetHeadLightWarmth(hw); LightKit->SetKeyToHeadRatio(hkh);
	LightKit->AddLightsToRenderer(leftRenderer);
	volumeProperty->SetShade(int(shading));
	volume->SetProperty(volumeProperty);
	//GetInteractor()->Render();
	render();
}

void vtkwidget::updatevolcol(double vc)
{

	mapper->SetFinalColorLevel(vc);
	GetInteractor()->Render();

}


void vtkwidget::updatewincol(double wcol)
{
	mapper->SetFinalColorWindow(wcol);
	GetInteractor()->Render();
}


void vtkwidget::readvti(string inputFilename)
{
	vtkXMLImageDataReader *rvti = vtkXMLImageDataReader::New();

	rvti->SetFileName(inputFilename.c_str());
	rvti->Update();
       imgmax=rvti->GetOutput()->GetScalarTypeMax();
	resample(rvti->GetOutput());
	rvti->Delete();
	
}

void vtkwidget::readtif(string inputFilename)
{
	//vtkTIFFReader *rtiff = vtkTIFFReader::New();
	readertiff->SetFileName(inputFilename.c_str());
    //readertiff->SetOrientationType(ORIENTATION_LEFTTOP);

	readertiff->Update();

    imgmax=readertiff->GetOutput()->GetScalarTypeMax();
	resample(readertiff->GetOutput());

	//rtiff->Delete();

}

void vtkwidget::resample(vtkImageData *imgdata)
{
	setvram();
   // mapper->SetMaxMemoryInBytes(vram);
	//Get the Graphics memory and find a scaling factor to match that, otherwise, render the imagedata without scaling
	vtkIdType memsize = imgdata->GetActualMemorySize();
   // cout<<mapper->GetMaxMemoryInBytes();
	double sf = ceil((memsize / vramvalue)/(1024*1024));

    if (sf>=1 && sf<8){
		sample_rate = 0.5;
	vtkSmartPointer <vtkImageResample> imgrs =vtkSmartPointer <vtkImageResample>::New();
	imgrs->SetInputData(imgdata);
    imgrs->SetInterpolationModeToCubic();
	imgrs->SetAxisMagnificationFactor(0, sample_rate);
	imgrs->SetAxisMagnificationFactor(1, sample_rate);
	imgrs->SetAxisMagnificationFactor(2, sample_rate);
	imgrs->Update();
	buildhist(imgrs->GetOutput());
	initialize(imgrs->GetOutput());
	}
    else if (sf >= 8 && sf < 16)

	{
		sample_rate = 0.25;
	vtkSmartPointer <vtkImageResample> imgrs = vtkSmartPointer <vtkImageResample>::New();
	imgrs->SetInputData(imgdata);
    imgrs->SetInterpolationModeToCubic();
	imgrs->SetAxisMagnificationFactor(0, sample_rate);
	imgrs->SetAxisMagnificationFactor(1, sample_rate);
	imgrs->SetAxisMagnificationFactor(2, sample_rate);
	imgrs->Update();
	buildhist(imgrs->GetOutput());
	initialize(imgrs->GetOutput());
	}
    else if (sf >= 16 && sf < 24)

	{
		sample_rate = 0.125;
	vtkSmartPointer <vtkImageResample> imgrs = vtkSmartPointer <vtkImageResample>::New();
	imgrs->SetInputData(imgdata);
    imgrs->SetInterpolationModeToCubic();
	imgrs->SetAxisMagnificationFactor(0, sample_rate);
	imgrs->SetAxisMagnificationFactor(1, sample_rate);
	imgrs->SetAxisMagnificationFactor(2, sample_rate);
	imgrs->Update();
	buildhist(imgrs->GetOutput());
	initialize(imgrs->GetOutput());
	}
	else if (sf<1)
	{
		sample_rate = 1;
		vtkSmartPointer <vtkImageResample> imgrs = vtkSmartPointer <vtkImageResample>::New();
		imgrs->SetInputData(imgdata);
		buildhist(imgrs->GetOutput());
		initialize(imgrs->GetOutput());
	}
	imgdata->ReleaseData();
}

void vtkwidget::readimseq(QString filetype, vtkStringArray *filenames, int N)
{
	setvram();
	if (filetype == QString("tiff") || filetype == QString("tif"))
	{
		vtkSmartPointer<vtkTIFFReader>readimg = vtkSmartPointer<vtkTIFFReader>::New();

		readimg->SetFileName(filenames->GetValue(0));
		readimg->Update();
		imgmax = readimg->GetOutput()->GetScalarTypeMax();
		int scalarsize = readimg->GetOutput()->GetScalarSize();
		int cols = readimg->GetOutput()->GetNumberOfScalarComponents();
		readimg->GetOutput()->GetDimensions(dims);
		dims[2] = N;
		double size = (double(dims[0]) * double(dims[1]) * double(dims[2])* double(cols)) / (1024 * 1024 * 1024);

		double sf = size / (vramvalue * 0.75);
		cout << size;
		vtkSmartPointer<vtkImageAppend> appendmag = vtkSmartPointer<vtkImageAppend>::New();


		int mf;

		appendmag->SetAppendAxis(2);
		if (sf >= 1 && sf < 8) { mf = 2; sample_rate = 0.5; }
		else if (sf >= 8 && sf < 64) { mf = 4; sample_rate = 0.25; }
		else if (sf < 1) { mf = 1; sample_rate = 1; }

		int m = 0;
		int num = ceil(N / mf) - 1;
		QProgressDialog progress("Loading files...", "Abort", 0, num, this);
		progress.setWindowModality(Qt::WindowModal);



		//imgrs->Update();
		//imgrs->ReleaseDataFlagOn();




#pragma omp parallel
		for (int i = 0; i < num; i++)
		{

			progress.setValue(i);
			if (progress.wasCanceled())
			{
				return;
				this->deleteLater();
			}
			//	vtkSmartPointer<vtkTIFFReader>readimg1 = vtkSmartPointer<vtkTIFFReader>::New();

			vtkSmartPointer<vtkTIFFReader>readimg0 = vtkSmartPointer<vtkTIFFReader>::New();

			vtkSmartPointer<vtkImageAppend> append = vtkSmartPointer<vtkImageAppend>::New();
			append->SetAppendAxis(2);

			for (int sc = 0; sc < mf; sc++)
			{

				readimg0->SetFileName(filenames->GetValue(mf*i + sc));
				readimg0->Update();
				append->AddInputConnection(readimg0->GetOutputPort());
				append->Update();


			}

			m++;

			vtkSmartPointer <vtkImageResample> imgrs = vtkSmartPointer <vtkImageResample>::New();
			imgrs->SetInterpolationModeToCubic();
			imgrs->SetAxisMagnificationFactor(0, sample_rate);
			imgrs->SetAxisMagnificationFactor(1, sample_rate);
			imgrs->SetAxisMagnificationFactor(2, sample_rate);
			imgrs->SetInputConnection(append->GetOutputPort());
			imgrs->Update();



			appendmag->AddInputData(imgrs->GetOutput());




		}

		progress.setValue(num);
		appendmag->Update();
		buildhist(appendmag->GetOutput());
		initialize(appendmag->GetOutput());
	}

	else if (filetype == QString("bmp"))
	{
		// Read all the DICOM files in the specified directory.
		vtkSmartPointer<vtkBMPReader> readimg =
			vtkSmartPointer<vtkBMPReader>::New();
		readimg->SetFileName(filenames->GetValue(0));
		readimg->Update();
		imgmax = readimg->GetOutput()->GetScalarTypeMax();
		int scalarsize = readimg->GetOutput()->GetScalarSize();
		int cols = readimg->GetOutput()->GetNumberOfScalarComponents();
		readimg->GetOutput()->GetDimensions(dims);
		dims[2] = N;
		double size = (double(dims[0]) * double(dims[1]) * double(dims[2])* double(cols)) / (1024 * 1024 * 1024);

		double sf = size / (vramvalue * 0.75);
		cout << size;
		vtkSmartPointer<vtkImageAppend> appendmag = vtkSmartPointer<vtkImageAppend>::New();
		

		int mf;

		appendmag->SetAppendAxis(2);
		if (sf >= 1 && sf < 8) { mf = 2; sample_rate = 0.5; }
		else if (sf >= 8 && sf < 64) { mf = 4; sample_rate = 0.25; }
		else if (sf < 1) { mf = 1; sample_rate = 1; }

		int m = 0;
		int num = ceil(N / mf) - 1;
		QProgressDialog progress("Loading files...", "Abort", 0, num, this);
		progress.setWindowModality(Qt::WindowModal);



		//imgrs->Update();
		//imgrs->ReleaseDataFlagOn();




#pragma omp parallel
		for (int i = 0; i < num; i++)
		{

			progress.setValue(i);
			if (progress.wasCanceled())
			{
				return;
				this->deleteLater();
			}
			//	vtkSmartPointer<vtkTIFFReader>readimg1 = vtkSmartPointer<vtkTIFFReader>::New();

			vtkSmartPointer<vtkBMPReader>readimg0 = vtkSmartPointer<vtkBMPReader>::New();

			vtkSmartPointer<vtkImageAppend> append = vtkSmartPointer<vtkImageAppend>::New();
			append->SetAppendAxis(2);

			for (int sc = 0; sc < mf; sc++)
			{

				readimg0->SetFileName(filenames->GetValue(mf*i + sc));
				readimg0->Update();
				append->AddInputConnection(readimg0->GetOutputPort());
				append->Update();


			}

			m++;

			vtkSmartPointer <vtkImageResample> imgrs = vtkSmartPointer <vtkImageResample>::New();
			imgrs->SetInterpolationModeToCubic();
			imgrs->SetAxisMagnificationFactor(0, sample_rate);
			imgrs->SetAxisMagnificationFactor(1, sample_rate);
			imgrs->SetAxisMagnificationFactor(2, sample_rate);
			imgrs->SetInputConnection(append->GetOutputPort());
			imgrs->Update();



			appendmag->AddInputData(imgrs->GetOutput());




		}

		progress.setValue(num);
		appendmag->Update();
		buildhist(appendmag->GetOutput());
		initialize(appendmag->GetOutput());
		
	}
}

void vtkwidget::buildhist(vtkImageData* imgdata)
{
	vtkSmartPointer<vtkImageAccumulate> histogram =
		vtkSmartPointer<vtkImageAccumulate>::New();
	histogram->SetInputData(imgdata);
    histogram->SetComponentExtent(0, imgmax, 0, 0, 0, 0);
	histogram->SetComponentOrigin(0, 0, 0);
	histogram->SetComponentSpacing(1, 0, 0);
	histogram->IgnoreZeroOn();
	histogram->Update();
    QVector<double> freq(imgmax+1);
	int* output = static_cast<int*>(histogram->GetOutput()->GetScalarPointer());
	
    for (int j = 0; j < imgmax+1; ++j)
	{

		freq[j] = *output++;
				
	}
	freq[0] = 0;
	
	emit sendhist(freq);
}

