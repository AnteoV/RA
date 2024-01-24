using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EndOfLevel : MonoBehaviour
{
    public GameObject levelToLoad;
    public GameObject currentLevel;
    public int levelNumber;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    void OnTriggerEnter2D(Collider2D other)
    {
        if (other.CompareTag("Ball"))
        {
            LevelSwitch();
            SaveProgress();
            other.GetComponent<MovementScript>().Respawn(other);
        }
    }

    private void LevelSwitch()
    {
        levelToLoad.SetActive(true);
        currentLevel.SetActive(false);
    }

    public void SaveProgress()
    {
        PlayerPrefs.SetInt("progress", levelNumber);
    }
}
