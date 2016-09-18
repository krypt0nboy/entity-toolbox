<?php

/**
 * Class PropertyFormsBuilder
 */
class EntityToolboxInfoPropertyFormsBuilder extends EntityToolboxInfoPropertyDependentKeyBuilder {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'self_key'    => 'forms',
        'model_class' => 'EntityToolboxInfoPropertyFormsModel',
      ),
      $args
    );
    parent::__construct($args);
  }

  /** {{@inheritdoc}} */
  protected function genStructureFromModel() {
    $structure          = parent::genStructureFromModel();
    $keyBuildersClasses = array();
    $keyBuildersArgs    = array();
    foreach (array_keys($structure) as $formType) {
      $keyBuildersClasses[$formType] = 'EntityToolboxInfoPropertyFormBuilder';
      $keyBuildersArgs[$formType]    = array(
        'form_type' => $formType,
      );
    }
    $this->__set('key_builders_classes', $keyBuildersClasses);
    $this->__set('key_builders_args', $keyBuildersArgs);

    return $structure;
  }

  /**
   * Build the "edit form".
   *
   * @return array
   */
  protected function buildPropertyEditForm() {
    return $this->getKeyBuilder('edit')->build();
  }
}