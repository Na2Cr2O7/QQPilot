using IniParser;
using IniParser.Model;
using Opt;
using System.Text;
using static System.Runtime.InteropServices.JavaScript.JSType;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;
namespace update
{
    public partial class Form1 : Form
    {
        private const string CONFIG_FILE_NAME = "config.ini";
        static readonly string ConfigPath = CONFIG_FILE_NAME;
        private string? OldDir;
        private Dictionary<string, string> iniPair = new();
        private Dictionary<string, string> newIniPair = new();
        private IniData? dataNew;
        FileIniDataParser parser = new();
        private string Version = "";
        private System.Text.UTF8Encoding Encoding = new System.Text.UTF8Encoding(false);
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {

            var ok = folder.ShowDialog();
            if (ok == DialogResult.OK)
            {
                textBox1.Text = folder.SelectedPath;
                OldDir = folder.SelectedPath;
            }
            if(OldDir is null)
            {
                return;
            }
            var data = parser.ReadFile(Path.Combine([OldDir, CONFIG_FILE_NAME]));
            try
            {
                vsOld.Text = "旧版本：" + data["general"]["version"];
            }
            catch
            {
                vsOld.Text = "未查询到旧版本号";
            }
        }
        private void GetConfig()
        {
            if (OldDir == null)
            {
                MessageBox.Show("未输入目录", "错误", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                return;
            }
            if (OldDir==Environment.CurrentDirectory)
            {
                MessageBox.Show("旧版本和新版本目录相同","错误",MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                return;
            }

            string oldConfigFile = Path.Combine([OldDir, CONFIG_FILE_NAME]);
            if (!File.Exists(oldConfigFile))
            {
                MessageBox.Show("没有找到旧版本配置文件", "错误", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                return;
            }
            string newConfigFile = Path.Combine([Environment.CurrentDirectory, CONFIG_FILE_NAME]);
            if (!File.Exists(newConfigFile))
            {
                return;
            }
            
            dataNew = parser.ReadFile(newConfigFile, Encoding);
            IniData dataOld = parser.ReadFile(oldConfigFile, Encoding);


            foreach (KeyData? i in dataOld["general"])
            {
                iniPair[i.KeyName]=i.Value;
                //label1.Text += $"{i.KeyName}:{i.Value}\n";
           
            }


            foreach (KeyData? i in dataNew["general"])
            {
                if(!iniPair.ContainsKey(i.KeyName))
                {
                    iniPair[i.KeyName] = i.Value;

                }
                //label1.Text += $"{i.KeyName}:{i.Value}\n";

            }
            foreach(KeyValuePair<string, string> i in iniPair)
            {
                dataNew["general"][i.Key]=i.Value.ToString();
            }
            dataNew["general"]["version"] = Version;
            parser.WriteFile(CONFIG_FILE_NAME, dataNew, Encoding);
            //parserNew.~FileIniDataParser();


        }
        private void CleanFile()
        {
            if(OldDir is null)
            {
                return;
            }
            List<string> files = [];
            foreach (var file in Directory.EnumerateFiles(OldDir, "*.*"))
            {
                File.Delete(Path.Combine([OldDir,file]));
                status.Text += $" X {Path.Combine([OldDir, file])}\n";
            }
            foreach (var file in Directory.EnumerateFiles(Environment.CurrentDirectory,"*.*"))
            {
                try
                {
                    
                    //status.Text += $"{Path.GetFileName(file)}->{OldDir}~~{Path.Combine([Environment.CurrentDirectory, file])}+{Path.Combine([OldDir, file])}\n";
 
                      File.Copy(Path.Combine([Environment.CurrentDirectory, file]), Path.Combine([OldDir, Path.GetFileName(file)]));
                }
                catch(Exception e)
                {
                
                    MessageBox.Show(e.Message,"错误",MessageBoxButtons.OK,MessageBoxIcon.Error);
                }
                status.Text += $" + {Path.Combine([OldDir, file])}\n";


                //pip
                File.WriteAllText(Path.Combine([OldDir, "Final.cmd"]), "PythonPath.cmd -m pip install -r requirements.txt", Encoding);

            }
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            splash Splash = new()
            {
                SizeofForm = this.Size,
                LocationofForm = new System.Numerics.Vector2(this.Location.X, this.Location.Y)
            };
            var data = parser.ReadFile(CONFIG_FILE_NAME, Encoding);
            Version = data["general"]["version"];
            vsNew.Text = data["general"]["version"];
            Splash.Show();
            Splash.BringToFront();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            status.Text = "";
            status.Text += "整理配置文件\n";
            GetConfig();
            status.Text += "更新文件\n";

            CleanFile();

            MessageBox.Show("迁移已经完成，\n你可能需要在文件夹中运行Final.cmd安装新的python库。","",MessageBoxButtons.OK,MessageBoxIcon.Information);
        }
    }
}
