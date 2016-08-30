<?php

/**
 * Class EntityDependentHookBuilder
 */
class EntityDependentHookBuilder extends HookBuilder {
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

  protected function preSetKeyBuildersClasses() {
    $this->__set('model_class', $this->constructArgs['model_class']);
  }

  protected function preSetModelClass() {
    $this->__set('entity_type', $this->constructArgs['entity_type']);
  }

  /**
   * @param       $keyBuilderClass
   * @param array $args
   *
   * @return mixed
   */
  protected function keyBuilderGetInstance($keyBuilderClass, array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'entity_type' => $this->constructArgs['entity_type'],
    ), $args);

    return parent::keyBuilderGetInstance($keyBuilderClass, $args);
  }
}