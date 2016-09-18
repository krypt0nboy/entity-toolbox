<?php

/**
 * Class LabelsValueBuilder
 */
class EntityToolboxInfoLabelsBuilder extends EntityToolboxInfoKeyBuilder {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'model_class' => 'EntityToolboxInfoLabelsRecursiveModel',
        'self_key'    => 'labels',
      ),
      $args
    );
    parent::__construct($args);
  }

  /**
   * Builds the value "single".
   *
   * @return string
   */
  protected function buildSingle() {
    return entity_type2entity_label($this->entityType);
  }

  /**
   * Builds the value "plural".
   *
   * @return string
   */
  protected function buildPlural() {
    return entity_type2entity_label_plural($this->entityType);
  }

  /**
   * @return string
   */
  protected function buildMachineNamePlural() {
    return entity_type_single2plural($this->entityType);
  }

  /**
   * @return string
   */
  protected function buildSingleLowerCase() {
    return lcfirst($this->getBuild('single'));
  }

  /**
   * @return string
   */
  protected function buildPluralLowerCase() {
    return lcfirst($this->getBuild('plural'));
  }

  /** {{@inheritdoc}} */
  protected function updateParentBuilderTemplateVars(array $args = array()) {
    $vars = array(
      'toolbox_info_labels_single'              => $this->getBuild('single'),
      'toolbox_info_labels_plural'              => $this->getBuild('plural'),
      'toolbox_info_labels_single_lowercase'    => $this->getBuild('single lowercase'),
      'toolbox_info_labels_plural_lowercase'    => $this->getBuild('plural lowercase'),
      'toolbox_info_labels_machine_name_plural' => $this->getBuild('machine_name plural'),
    );
    parent::updateParentBuilderTemplateVars($vars);
  }
}