using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LoaderScript : MonoBehaviour
{
    private GameObject sh;
    private GameObject es;

    void Start()
    {
        LoadProgress();
        sh = this.gameObject;
        es = GameObject.Find("EndScreen");
    }

    
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Escape) && es==null )
        {
            sh.GetComponent<MainMenuScript>().LoadSceneOnPress(0);
        }
    }

    public void LoadProgress()
    {
        int level = PlayerPrefs.GetInt("progress", 1);
        string levelText;
        for(int i=1; i<=10; i++)
        {
            levelText = "Level" + i;
            GameObject levelObject = GameObject.Find(levelText);
            if(level != i) 
            {
                levelObject.SetActive(false);
            }
        }
    }
}
