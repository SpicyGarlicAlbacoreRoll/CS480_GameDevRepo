using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
public class scoreManager : MonoBehaviour
{
    // Start is called before the first frame update
    [SerializeField] public GameObject score;
    [SerializeField] public GameObject multiplier;
    [SerializeField] public GameObject timer;
    [SerializeField] public GameObject Results;
    [SerializeField] public GameObject Stats;
    private float score_multiplier = 1;
    private float current_score = 0;
    private float startTime = 0.0f;
    private float time = 0;
    private int currentMultiplier = 0;
    private bool gameOverState = false;
    private bool gameOverScreen = false;
    private bool scoresSeen = false;
    void Start()
    {
        Results.SetActive(false);
        startTime = Time.time;
    }

    // Update is called once per frame
    void Update()
    {
        if (!gameOverScreen)
        {
            if (!gameOverState)
            {
                updateScore();
                updateUI();
            }
            else
            {
                gameOver();
            }
        } else {
            if(Input.GetKeyDown(KeyCode.Return) && scoresSeen) {
                SceneManager.LoadScene(SceneManager.GetActiveScene().name);
                // scoresSeen = false;
            }
        }
    }

    private void updateScore()
    {
        time = Time.time - startTime;

        if (Mathf.FloorToInt(time) % 8 == 0 && currentMultiplier != Mathf.FloorToInt(time) && score_multiplier != 128)
        {
            currentMultiplier = Mathf.FloorToInt(time);
            score_multiplier *= 2;
        }
        current_score += (score_multiplier * Time.deltaTime) * 100.0f;
    }

    private void updateUI()
    {
        int x = 32 + Mathf.FloorToInt(score_multiplier) * 2;
        // Color multiplier_color = new Color(1.0f, 1.0f - (score_multiplie, 1.0f, 1.0f);
        Color multiplier_color = Color.Lerp(Color.white, Color.red, score_multiplier / 32.0f);
        string color_string = ColorUtility.ToHtmlStringRGBA(multiplier_color);
        score.GetComponent<Text>().text = $"SCORE: <b>{Mathf.FloorToInt(current_score)}</b>";
        multiplier.GetComponent<Text>().text = $"MULTIPLIER: <color=#{color_string}><size={x}><b>{score_multiplier}</b></size></color>";
        timer.GetComponent<Text>().text = $"TIME: <b>{Mathf.FloorToInt(time)}</b>";
    }

    public void resetUI()
    {
        score.GetComponent<Text>().text = "0";
        multiplier.GetComponent<Text>().text = "0";
        timer.GetComponent<Text>().text = "0";

        time = 0;
        score_multiplier = 1;
        current_score = 0;
    }
    public void gameOver()
    {
        gameOverScreen = true;
        StartCoroutine("displayGameOver");
    }

    public void game_over_event()
    {
        gameOverState = true;
    }

    IEnumerator displayGameOver() {
        float displayScoreTime = 5.0f;

        score.SetActive(false);
        multiplier.SetActive(false);
        timer.SetActive(false);
        Results.SetActive(true);
        Color multiplier_color = Color.Lerp(Color.white, Color.red, score_multiplier / 32.0f);
        string color_string = ColorUtility.ToHtmlStringRGBA(multiplier_color);
        Stats.GetComponent<Text>().text = $"SCORE: <b>{Mathf.FloorToInt(current_score)}</b>\nMULTIPLIER: <color=#{color_string}><b>{score_multiplier}</b></color>\nTIME: <b>{Mathf.FloorToInt(time)}</b>";
        yield return new WaitForSeconds(displayScoreTime);
        Results.GetComponent<Text>().text = "Play Again?";
        Stats.GetComponent<Text>().text = " (Press Enter)";
        scoresSeen = true;
    }
}
