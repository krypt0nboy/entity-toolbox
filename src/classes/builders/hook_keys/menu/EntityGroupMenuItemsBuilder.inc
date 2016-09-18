<?php

/**
 * Class EntityGroupMenuItemsBuilder
 */
class EntityGroupMenuItemsBuilder extends MenuKeyBuilder {
  /**
   * @var string $entityGroup
   */
  protected $entityGroup;
  /**
   * @var array $entityGroupInfo
   */
  protected $entityGroupInfo = array();

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'structure'            => array(
        '%entity_group_info_path%' => array(
          'type'   => 'array',
          'method' => 'buildEntityGroupRootMenuItem'
        )
      ),
      'key_builders_classes' => array(
        '%entity_group_info_path%' => 'EntityGroupMenuItemBuilder'
      )
    ), $args);
    parent::__construct($args);
  }

  /**
   * @return string
   */
  public function getEntityGroup() {
    return $this->entityGroup;
  }

  /**
   * @param string $entityGroup
   */
  public function setEntityGroup($entityGroup) {
    $this->entityGroup = $entityGroup;
  }

  protected function postSetEntityGroup() {
    $this->__set('entity_group_info', entity_toolbox_entity_group_get_info($this->entityGroup));
  }

  /**
   * @return array
   */
  public function getEntityGroupInfo() {
    return $this->entityGroupInfo;
  }

  /**
   * @param array $entityGroupInfo
   */
  public function setEntityGroupInfo($entityGroupInfo) {
    $this->entityGroupInfo = $entityGroupInfo;
  }

  protected function buildEntityGroupRootMenuItem() {

  }
}