//------------------------------------------------------------------------------
// <copyright file="DIY.cs" company="Company">
//     Copyright (c) Company.  All rights reserved.
// </copyright>
//------------------------------------------------------------------------------

using System;
using System.ComponentModel.Design;
using System.Diagnostics;
using System.Diagnostics.CodeAnalysis;
using System.Globalization;
using System.Runtime.InteropServices;
using Microsoft.VisualStudio;
using Microsoft.VisualStudio.OLE.Interop;
using Microsoft.VisualStudio.Shell;
using Microsoft.VisualStudio.Shell.Interop;
using Microsoft.Win32;
using System.Windows.Forms;

namespace DIY
{
    /// <summary>
    /// This is the class that implements the package exposed by this assembly.
    /// </summary>
    /// <remarks>
    /// <para>
    /// The minimum requirement for a class to be considered a valid package for Visual Studio
    /// is to implement the IVsPackage interface and register itself with the shell.
    /// This package uses the helper classes defined inside the Managed Package Framework (MPF)
    /// to do it: it derives from the Package class that provides the implementation of the
    /// IVsPackage interface and uses the registration attributes defined in the framework to
    /// register itself and its components with the shell. These attributes tell the pkgdef creation
    /// utility what data to put into .pkgdef file.
    /// </para>
    /// <para>
    /// To get loaded into VS, the package must be referred by &lt;Asset Type="Microsoft.VisualStudio.VsPackage" ...&gt; in .vsixmanifest file.
    /// </para>
    /// </remarks>
    /// 
    [ProvideAutoLoad(UIContextGuids.NoSolution)]
    [ProvideAutoLoad(UIContextGuids.SolutionExists)]
    [PackageRegistration(UseManagedResourcesOnly = true)]
    [InstalledProductRegistration("#110", "#112", "1.0", IconResourceID = 400)] // Info on this package for Help/About
    [Guid(DIY.PackageGuidString)]
    [SuppressMessage("StyleCop.CSharp.DocumentationRules", "SA1650:ElementDocumentationMustBeSpelledCorrectly", Justification = "pkgdef, VS and vsixmanifest are valid VS terms")]

    public sealed class DIY : Package
    {
        /// <summary>
        /// DIY GUID string.
        /// </summary>
        public const string PackageGuidString = "e73ed199-2649-4ad0-9fd6-c98a39b1a429";

        /// <summary>
        /// Initializes a new instance of the <see cref="DIY"/> class.
        /// </summary>
        public DIY()
        {
            // Inside this method you can place any initialization code that does not require
            // any Visual Studio service because at this point the package object is created but
            // not sited yet inside Visual Studio environment. The place to do all the other
            // initialization is the Initialize method.
            Debug.WriteLine(string.Format(CultureInfo.CurrentCulture, "Entering constructor for: {0}", this.ToString()));
        }

        #region Package Members

        /// <summary>
        /// Initialization of the package; this method is called right after the package is sited, so this is the place
        /// where you can put all the initialization code that rely on services provided by VisualStudio.
        /// </summary>
        protected override void Initialize()
        {
            Debug.WriteLine(string.Format(CultureInfo.CurrentCulture, "Entering Initialize() of: {0}", this.ToString()));
            base.Initialize();
            Application.Current.MainWindow.Loaded += MainWindow_Loaded;
        }
        void MainWindow_Loaded(object sender, RoutedEventArgs e)
        {
            var rWindow = (Window)sender;

            //加载图片
            var rImageSource = BitmapFrame.Create(new Uri(@"E:\\孤影\\照片\\桌面\\shut.jpg"/*图片路径*/), BitmapCreateOptions.None, BitmapCacheOption.OnLoad);
            rImageSource.Freeze();

            var rImageControl = new Image()
            {
                Source = rImageSource,
                Stretch = Stretch.UniformToFill, //按比例填充
                HorizontalAlignment = HorizontalAlignment.Center, //水平方向中心对齐
                VerticalAlignment = VerticalAlignment.Center, //垂直方向中心对齐
            };

            Grid.SetRowSpan(rImageControl, 4);
            var rRootGrid = (Grid)rWindow.Template.FindName("RootGrid", rWindow);
            rRootGrid.Children.Insert(0, rImageControl);
        }

        读取指定的图片资源,填充到Visual Studio IDE编辑器中

        #endregion
    }
}
