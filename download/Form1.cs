using Opt;

namespace download
{
    public partial class Form1 : Form
    {
        private HttpClient httpClient;
        private CancellationTokenSource cts;
        private string download = "https://ollama.com/download/OllamaSetup.exe";
        public Form1()
        {
            InitializeComponent();
            httpClient = new HttpClient();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            splash Splash = new()
            {
                SizeofForm = this.Size,
                LocationofForm = new System.Numerics.Vector2(this.Location.X, this.Location.Y)
            };
            status.Text = "准备就绪";
            status.AutoSize = true;
            cancel.Visible = false;

        }

        private async void button1_Click(object sender, EventArgs e)
        {
            
            string savePath = Path.Combine([Application.StartupPath, "OllamaSetup.exe"]);
            button1.Enabled = false;
            if (File.Exists(savePath))
            {
                button1.Enabled = true;
                MessageBox.Show("下载文件已经存在", "", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }
            try
            {
                cancel.Visible = true;
                cts = new CancellationTokenSource();
                await DownloadFileAsync(download, savePath, progressBar1, cts.Token);
                MessageBox.Show("下载完成！", "成功", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (OperationCanceledException)
            {
                MessageBox.Show("下载已取消", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (Exception ex)
            {
                MessageBox.Show($"下载失败: {ex.Message}", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            finally
            {
                button1.Enabled = true;
                cancel.Visible = false;
                status.Text = "";
            }

        }
        private string FormatSize(long bytes)
        {
            string[] sizes = { "B", "KB", "MB", "GB" };
            int order = 0;
            double len = bytes;
            while (len >= 1024 && order < sizes.Length - 1)
            {
                order++;
                len /= 1024;
            }
            return $"{len:0.##} {sizes[order]}";
        }

        private async Task DownloadFileAsync(string url, string filePath, ProgressBar progressBar, CancellationToken token)
        {
            using (var response = await httpClient.GetAsync(url, HttpCompletionOption.ResponseHeadersRead, token))
            {
                response.EnsureSuccessStatusCode();

                long totalBytes = response.Content.Headers.ContentLength ?? -1;
                using (var contentStream = await response.Content.ReadAsStreamAsync())
                using (var fileStream = new System.IO.FileStream(filePath, System.IO.FileMode.Create, System.IO.FileAccess.Write))
                {
                    var buffer = new byte[8192];
                    long totalBytesRead = 0;
                    int bytesRead;

                    while ((bytesRead = await contentStream.ReadAsync(buffer, 0, buffer.Length, token)) > 0)
                    {
                        await fileStream.WriteAsync(buffer, 0, bytesRead, token);
                        totalBytesRead += bytesRead;

                        if (totalBytes != -1)
                        {
                            int progressPercentage = (int)((double)totalBytesRead / totalBytes * 100);
                            progressBar.Invoke((MethodInvoker)delegate
                            {
                                progressBar.Value = progressPercentage;
                                status.Text = $"下载中... {FormatSize(totalBytesRead)} / {FormatSize(totalBytes)} ({progressPercentage}%)";
                                //this.Controls["lblStatus"].Text = 
                            });
                        }
                    }
                }
            }
        }

        private void cancel_Click(object sender, EventArgs e)
        {
            if (cts != null && !cts.IsCancellationRequested)
            {
                cts.Cancel();
            }
        }

        private void status_Click(object sender, EventArgs e)
        {

        }
    }

}
