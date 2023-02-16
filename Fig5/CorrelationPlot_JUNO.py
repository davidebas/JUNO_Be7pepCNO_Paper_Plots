# Author: Davide Basilico - 2022

import numpy as np
import pandas as pd
#import tkinter
import matplotlib as mpl
import matplotlib.pyplot as plt
import sys
import matplotlib.patches as patches
from scipy.stats import gaussian_kde
import os
import matplotlib.ticker as ticker
from decimal import Decimal

# plt.rc('text',usetex=True)
#mpl.rcParams['text.latex.preamble'] = ['\\usepackage{siunitx}']
# mpl.rcParams['text.latex.preamble'] = ['\\usepackage{mhchem}']
pgf_with_latex = {                      # setup matplotlib to use latex for output# {{{
    "pgf.texsystem": "pdflatex",        # change this if using xetex or lautex
    "text.usetex": True,                # use LaTeX to write all text
    "font.family": "serif",
    "font.serif": ['Computer Modern'],                   # blank entries should cause plots
    "font.sans-serif": [],              # to inherit fonts from the document
    "font.monospace": [],
    "axes.labelsize": 14,               # LaTeX default is 10pt font.
    "font.size": 14,
    "legend.fontsize": 14,               # Make the legend/label fonts
    "xtick.labelsize": 16,               # a little smaller
    "ytick.labelsize": 16,
    "pgf.preamble": [
        r"\usepackage[utf8x]{inputenc}",    # use utf8 fonts
        r"\usepackage[T1]{fontenc}",        # plots will be generated
        r"\usepackage[detect-all,locale=DE_nu]{siunitx}",
        ]                                   # using this preamble
    }
# }}}

#mpl.rcParams.update(pgf_with_latex)

InputTextFile = sys.argv[1]

df2 = pd.read_csv(InputTextFile,delimiter='	')
#df = df2.query('Be7_Rec<70')
df = df2.query('abs(Be7_RMS)/Be7_Rec*100<20 & abs(pep_RMS)/pep_Rec*100<70 & abs(Be7_Rec-Be7_Inj)/Be7_RMS<3 & abs(pep_Rec-pep_Inj)/pep_RMS<3 & abs(CNO_Rec-CNO_Inj)/CNO_RMS<3')
#df = df2.query('Be7_Rec<70')

print(len(df['Be7_Rec']))

NamesAll = ['Be7','pep','CNO','Bi210','Po210','K40','Kr85','U238','Th232','C11','C11_2','He6_2']

Names = ['Be7','pep','CNO','Bi210','Po210','K40','Kr85','U238','Th232','C11','C11_2']
NamesLabels = ['$^{7}$Be','pep','CNO','$^{210}$Bi','$^{210}$Po','$^{40}$K','$^{85}$Kr','$^{238}$U','$^{232}$Th','$^{11}\mathrm{C_{sub}}$','$^{11}\mathrm{C_{tag}}$']

N = len(Names)

Inj = [None] * N
InjAll = [None] * len(NamesAll)
RelSigmaSigma = [None] * len(NamesAll)

for i in range (0,len(NamesAll)):
	df[NamesAll[i] + '_Inj'] = df[NamesAll[i] + '_Inj']*10
	InjAll[i] = df[NamesAll[i] + '_Inj'].mean()
	df[NamesAll[i]+'_Rec'] = df[NamesAll[i]+'_Rec']*10
	df[NamesAll[i]+'_RMS'] = df[NamesAll[i]+'_RMS']*10
	
for i in range (0,N):
	Inj[i] = df[Names[i] + '_Inj'].mean()

fig = plt.figure(figsize=(2.4*N,2.4*N))

Bins = 20
NSigma = 3

GDL = 2*(2400-650)-12

print('Par' + '\t' + 'InjPar_Mean' + '\t' + 'RecPar_Mean' + '\t' + 'RMS' + '\t\t' + 'RelRMS[%]' + '\t' + 'NewRRMSError[%]' + '\t' + 'RelRMSError[%]' + '\t' + 'Bias[%]')

for i in range(len(NamesAll)):
	
	InjAll[i] = df[NamesAll[i] + '_Inj'].mean()
	
	RelSigmaSigma[i] =( (df[NamesAll[i]+'_Rec'].std())**1  * np.sqrt(1/(2*GDL-2))/df[NamesAll[i]+'_Rec'].mean()*100. )
	
	print(str(NamesAll[i]) + '\t' + "%.3e" % InjAll[i] + '\t' + "%.3e" % df[NamesAll[i]+'_Rec'].mean() + '\t' + "%.3e" % df[NamesAll[i]+'_Rec'].std() + '\t' + "%.3f" % (df[NamesAll[i]+'_Rec'].std()/df[NamesAll[i]+'_Rec'].mean()*100.) + '\t\t' + "%.3e" % RelSigmaSigma[i] + '\t' + "%.3f" % (df[NamesAll[i]+'_RMS'].std()/df[NamesAll[i]+'_Rec'].mean()*100.) + '\t\t' + "%.3f" % (100.*(df[NamesAll[i]+'_Rec'].mean()/InjAll[i]-1)))

### DIAGONAL PLOTS ###
for i in range (0,N):
	fig.add_subplot(N,N,(N+1)*i+1)

	df[Names[i]+'_Rec'].hist(color='red', histtype='bar', edgecolor='none',grid=False, bins=Bins)    
	plt.xlim(df[Names[i]+'_Rec'].mean()-4*df[Names[i]+'_Rec'].std(),df[Names[i]+'_Rec'].mean()+4*df[Names[i]+'_Rec'].std())
	x1, y1 = [Inj[i],Inj[i]], [0,len(df)/5.]   ## black vertical line
	if (i==0): plt.ylabel(NamesLabels[i] ,   size = 3.0*N);
	if (i==N-1): plt.xlabel(NamesLabels[i] ,   size = 3.0*N)		
	plt.yticks(fontsize=0)
	if (i==N-1): 
		plt.xticks(fontsize = 1.2*N, rotation=20)
		plt.xlabel(NamesLabels[i],labelpad=10)
	plt.plot(x1, y1, 'k', marker = '', linewidth=2, color='dimgrey')

plt.subplots_adjust(wspace=0, hspace=0)

### NON-DIAGONAL PLOTS ###
for i in range(N):
	for j in range(i):
		fig.add_subplot(N,N,i*N+j+1)
		xy = np.vstack([df[Names[i]+'_Rec'],df[Names[j]+'_Rec']])
		z = gaussian_kde(xy)(xy)	
		plt.scatter(df[Names[j]+'_Rec'],df[Names[i]+'_Rec'],c=z,s=10, cmap='jet',edgecolor='none')
		x1, y1 = [Inj[j],Inj[j]], [df[Names[i]+'_Rec'].mean()-4*df[Names[i]+'_Rec'].std(),df[Names[i]+'_Rec'].mean()+4*df[Names[i]+'_Rec'].std()]
		plt.plot(x1, y1, 'k', marker = '', linewidth=2, color='dimgrey')
		x2, y2 = [df[Names[j]+'_Rec'].mean()-4*df[Names[j]+'_Rec'].std(),df[Names[j]+'_Rec'].mean()+4*df[Names[j]+'_Rec'].std()],[Inj[i],Inj[i]]		
		plt.plot(x2, y2, 'k', marker = '', linewidth=2, color='dimgrey')
		plt.xlim(df[Names[j]+'_Rec'].mean()-4*df[Names[j]+'_Rec'].std(),df[Names[j]+'_Rec'].mean()+4*df[Names[j]+'_Rec'].std())
		plt.ylim(df[Names[i]+'_Rec'].mean()-4*df[Names[i]+'_Rec'].std(),df[Names[i]+'_Rec'].mean()+4*df[Names[i]+'_Rec'].std())
		if(i==N-1): 
			plt.xlabel(NamesLabels[j] ,   size = 3.0*N, rotation=0, labelpad=10)
			plt.xticks(fontsize = 1.2*N, rotation=20)
			plt.yticks(fontsize = 1.2*N)
			plt.xticks([round(df[Names[j]+'_Rec'].mean()-2.*df[Names[j]+'_Rec'].std(),1),round(df[Names[j]+'_Rec'].mean(),1),round(df[Names[j]+'_Rec'].mean()+2*df[Names[j]+'_Rec'].std(),1)])
			
		else: plt.xticks(fontsize=0)
		if(j==0):
			plt.ylabel(NamesLabels[i] ,   size = 3.0*N)
			plt.yticks(fontsize = 1.2*N)			
			plt.yticks([round(df[Names[i]+'_Rec'].mean()-2.*df[Names[i]+'_Rec'].std(),1),round(df[Names[i]+'_Rec'].mean(),1),round(df[Names[i]+'_Rec'].mean()+2*df[Names[i]+'_Rec'].std(),1)])
		else: plt.yticks(fontsize=0)		

OutputTextFile = 'Fig5.jpg'


OutputTextFile = os.path.basename(OutputTextFile)



print(OutputTextFile)

plt.savefig(OutputTextFile,bbox_inches='tight')

#' ' + str(df['pep_RMS'].std()) + ' ' + str(df['pep_RMS'].RMS()/str(df['pep_Rec'].mean()*100.)) + ' ' + str(df['CNO_RMS'].std()) + ' ' + str(df['CNO_RMS'].RMS()/str(df['CNO_Rec'].mean()*100.))


