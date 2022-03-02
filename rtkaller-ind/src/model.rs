// Copyright 2021, Developed by Tsinghua Wingtecher Lab and Shumuyulin Ltd, All rights reserved.
use serde::Deserialize;
use std::collections::HashMap;

bitflags! {
    #[derive(Deserialize)]
    pub struct HookType : u8{
        const ERROR =  0b0000_0001;
        const PRE_TASK = 0b0000_0010;
        const POST_TASK = 0b0000_0100;
        const STARTUP = 0b0000_1000;
        const SHUTDOWN = 0b0001_0000;
    }
}

pub type Id = String;

#[derive(Clone, Debug, Deserialize)]
pub struct ISR {
    pub is_isr1: bool,
    pub id: Id,
    pub handler: Option<String>,
}

impl ISR {
    pub fn new_isr2(id: Id, handler: Option<String>) -> Self {
        Self {
            is_isr1: false,
            id,
            handler,
        }
    }
}

#[derive(Clone, Debug, Deserialize)]
pub struct Task {
    pub id: Id,
    pub events: Vec<Id>,
    pub resources: Vec<Id>,
}

#[derive(Clone, Debug, Deserialize)]
pub struct APPConfig {
    pub enabled_hook: HookType,
    pub isr: Vec<ISR>,
    pub tasks: Vec<Task>,
    pub counters: Vec<Id>,
    pub alarms: Vec<Id>,
    pub sym_val: HashMap<Id, u32>,
}

impl Default for APPConfig {
    fn default() -> Self {
        Self {
            enabled_hook: HookType::ERROR
                | HookType::STARTUP
                | HookType::PRE_TASK
                | HookType::POST_TASK,
            isr: vec![
                ISR::new_isr2(
                    String::from("isr1_handler"),
                    Some(String::from("isr1_handler")),
                ),
                ISR::new_isr2(
                    String::from("isr2_handler"),
                    Some(String::from("isr2_handler")),
                ),
                ISR::new_isr2(
                    String::from("isr3_handler"),
                    Some(String::from("isr3_handler")),
                ),
            ],
            tasks: vec![
                Task {
                    id: "Task1".to_string(),
                    events: vec![String::from("Event1"), String::from("Event2")],
                    resources: vec![String::from("Resource1"), String::from("Resource2")],
                },
                Task {
                    id: "Task2".to_string(),
                    events: vec![String::from("Event1"), String::from("Event3")],
                    resources: vec![String::from("Resource1"), String::from("Resource3")],
                },
                Task {
                    id: "Task3".to_string(),
                    events: vec![String::from("Event2"), String::from("Event3")],
                    resources: vec![String::from("Resource2"), String::from("Resource3")],
                },
            ],
            counters: vec![String::from("Counter1"), String::from("Counter2")],
            alarms: vec![
                String::from("Alarm1"),
                String::from("Alarm2"),
                String::from("Alarm3"),
            ],
            sym_val: Default::default(),
        }
    }
}

#[derive(Debug, Clone)]
pub enum InstType {
    Task(Task),
    Isr(ISR),
    Hook(HookType),
}

#[cfg(test)]
mod tests {
    use super::APPConfig;
    use serde_json::from_str;

    #[test]
    fn deserialize_model() {
        const VAL: &str = r#"{
  "enabled_hook": { "bits" : 31 },
  "isr": [
    {
      "is_isr1": false,
       "id": "isr1_handler"
    },
    {
      "is_isr1": false,
      "id": "isr2_handler"
    },
    {
      "is_isr1": false,
      "id": "isr2_handler"
    }
  ],
  "tasks": [
    {
      "id": "Task1",
      "events": ["Event1","Event2"],
      "resources": ["Resource1", "Resource2"]
    },
    {
      "id": "Task2",
      "events": ["Event1","Event3"],
      "resources": ["Resource1", "Resource3"]
    },
    {
      "id": "Task1",
      "events": ["Event2","Event3"],
      "resources": ["Resource2", "Resource3"]
    }
  ],
  "counters": ["Counter1","Counter2"],
  "alarms": ["Alarm1","Alarm3","Alarm3"],

  "sym_val": {  "Task1": 0, "Task2": 1,"Task3": 2,
                "Event1": 0, "Event2": 1,"Event3": 2,
                "Resource1": 0, "Resource2": 1, "Resource3": 2,
                "Counter1": 0, "Counter2": 1,
                "Alarm1": 0, "Alarm2": 1, "Alarm3": 2}
}"#;

        let app: APPConfig = from_str(VAL).unwrap();
        assert!(app.enabled_hook.is_all());
    }
}
