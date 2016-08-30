<?php

/**
 * Class EntityDependentHookKeyBuilder
 */
class EntityDependentHookKeyBuilder extends HookKeyBuilder {
  /**
   * @var string $entityType
   */
  public $entityType;

  /**
   * @return string
   */
  public function getEntityType() {
    return $this->entityType;
  }

  /**
   * @param string $entityType
   */
  public function setEntityType($entityType) {
    $this->entityType = $entityType;
  }

  /**
   * @param       $keyBuilderClass
   * @param array $args
   *
   * @return mixed
   */
  protected function keyBuilderGetInstance($keyBuilderClass, array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'entity_type' => $this->entityType,
    ), $args);

    return parent::keyBuilderGetInstance($keyBuilderClass, $args);
  }

  protected function preSetKeyBuildersClasses() {
    parent::preSetKeyBuildersClasses();
    $this->__set('entity_type', $this->constructArgs['entity_type']);
  }
}