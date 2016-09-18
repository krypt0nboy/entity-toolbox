<?php

/**
 * Class EntityGroupDependentTraits
 */
trait EntityGroupDependentTraits {
  /**
   * @var string $groupName
   *   The group name.
   */
  protected $groupName;
  /**
   * @var array $groupInfo
   *   The group info.
   */
  protected $groupInfo = array();

  /**
   * @return string
   */
  public function getGroupName() {
    return $this->groupName;
  }

  /**
   * @param string $groupName
   */
  public function setGroupName($groupName) {
    $this->groupName = $groupName;
  }

  protected function postSetGroupName(){
  }

  /**
   * @return array
   */
  public function getGroupInfo() {
    return $this->groupInfo;
  }

  /**
   * @param array $groupInfo
   */
  public function setGroupInfo($groupInfo) {
    $this->groupInfo = $groupInfo;
  }

  /**
   * Auto sets groupInfo.
   */
  public function autoSetGroupInfo(){
    $this->__set('group_info', entity_toolbox_entity_group_get_info($this->groupName));
  }
}